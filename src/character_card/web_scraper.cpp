#include "character_card/web_scraper.h"
#include <sstream>
#include <regex>
#include <algorithm>

namespace AutoCoder {
namespace CharacterCard {

WebScraper::WebScraper() : curl(nullptr) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
}

WebScraper::~WebScraper() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

size_t WebScraper::writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string WebScraper::fetchWebPage(const std::string& url) {
    if (!curl) {
        return "";
    }

    std::string readBuffer;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "AutoCoder/1.0");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        if (progressCallback) {
            progressCallback(0, std::string("Error: ") + curl_easy_strerror(res));
        }
        return "";
    }

    return readBuffer;
}

std::vector<KinkCategory> WebScraper::scrapeKinksList(const std::string& url) {
    if (progressCallback) {
        progressCallback(10, "Fetching webpage...");
    }

    std::string html = fetchWebPage(url);

    if (html.empty()) {
        if (progressCallback) {
            progressCallback(0, "Failed to fetch webpage");
        }
        return {};
    }

    if (progressCallback) {
        progressCallback(50, "Parsing content...");
    }

    std::vector<KinkCategory> categories = parseKinksHtml(html);

    if (progressCallback) {
        progressCallback(100, "Complete!");
    }

    return categories;
}

void WebScraper::setProgressCallback(ProgressCallback callback) {
    progressCallback = callback;
}

std::vector<KinkCategory> WebScraper::parseKinksHtml(const std::string& html) {
    std::vector<KinkCategory> categories;

    // Extract list items from HTML
    // This is a simplified parser - in production, use a proper HTML parser like libxml2
    std::vector<std::string> items = extractListItems(html);

    if (!items.empty()) {
        KinkCategory category;
        category.name = "All Kinks";
        category.items = items;
        categories.push_back(category);
    }

    // Try to extract categorized content if available
    // Look for headings followed by lists
    std::regex headingPattern(R"(<h[2-6][^>]*>(.*?)</h[2-6]>)");
    std::regex listPattern(R"(<ul[^>]*>(.*?)</ul>)", std::regex::icase | std::regex::multiline);

    std::smatch match;
    std::string::const_iterator searchStart(html.cbegin());

    while (std::regex_search(searchStart, html.cend(), match, headingPattern)) {
        std::string heading = cleanHtmlText(match[1].str());

        // Look for list following this heading
        std::string remainingHtml(match.suffix().first, html.cend());
        std::smatch listMatch;

        if (std::regex_search(remainingHtml, listMatch, listPattern)) {
            std::string listContent = listMatch[1].str();
            std::vector<std::string> listItems = extractListItems(listContent);

            if (!listItems.empty()) {
                KinkCategory cat;
                cat.name = heading;
                cat.items = listItems;
                categories.push_back(cat);
            }
        }

        searchStart = match.suffix().first;
    }

    return categories;
}

std::vector<std::string> WebScraper::extractListItems(const std::string& html) {
    std::vector<std::string> items;

    // Extract <li> items
    std::regex liPattern(R"(<li[^>]*>(.*?)</li>)", std::regex::icase | std::regex::multiline);
    std::sregex_iterator iter(html.begin(), html.end(), liPattern);
    std::sregex_iterator end;

    while (iter != end) {
        std::string item = cleanHtmlText((*iter)[1].str());
        if (!item.empty()) {
            items.push_back(item);
        }
        ++iter;
    }

    // If no <li> items found, try to extract plain text lines
    if (items.empty()) {
        std::regex linkPattern(R"(<a[^>]*>(.*?)</a>)", std::regex::icase);
        std::sregex_iterator linkIter(html.begin(), html.end(), linkPattern);

        while (linkIter != end) {
            std::string item = cleanHtmlText((*linkIter)[1].str());
            if (!item.empty()) {
                items.push_back(item);
            }
            ++linkIter;
        }
    }

    return items;
}

std::string WebScraper::cleanHtmlText(const std::string& text) {
    // Remove HTML tags
    std::regex tagPattern(R"(<[^>]*>)");
    std::string cleaned = std::regex_replace(text, tagPattern, "");

    // Decode common HTML entities
    std::vector<std::pair<std::string, std::string>> entities = {
        {"&amp;", "&"},
        {"&lt;", "<"},
        {"&gt;", ">"},
        {"&quot;", "\""},
        {"&#39;", "'"},
        {"&nbsp;", " "},
        {"&mdash;", "—"},
        {"&ndash;", "–"}
    };

    for (const auto& entity : entities) {
        size_t pos = 0;
        while ((pos = cleaned.find(entity.first, pos)) != std::string::npos) {
            cleaned.replace(pos, entity.first.length(), entity.second);
            pos += entity.second.length();
        }
    }

    // Trim whitespace
    cleaned.erase(0, cleaned.find_first_not_of(" \t\n\r"));
    cleaned.erase(cleaned.find_last_not_of(" \t\n\r") + 1);

    return cleaned;
}

} // namespace CharacterCard
} // namespace AutoCoder
