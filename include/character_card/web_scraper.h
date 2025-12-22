#ifndef CHARACTER_CARD_WEB_SCRAPER_H
#define CHARACTER_CARD_WEB_SCRAPER_H

#include <string>
#include <vector>
#include <functional>
#include <curl/curl.h>

namespace AutoCoder {
namespace CharacterCard {

struct KinkCategory {
    std::string name;
    std::vector<std::string> items;
};

class WebScraper {
public:
    WebScraper();
    ~WebScraper();

    // Scrape kinks and fetishes from various sources
    std::vector<KinkCategory> scrapeKinksList(const std::string& url);

    // Generic web content fetcher
    std::string fetchWebPage(const std::string& url);

    // Progress callback
    using ProgressCallback = std::function<void(int progress, const std::string& status)>;
    void setProgressCallback(ProgressCallback callback);

private:
    CURL* curl;
    ProgressCallback progressCallback;

    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);

    // Parse HTML content
    std::vector<KinkCategory> parseKinksHtml(const std::string& html);
    std::vector<std::string> extractListItems(const std::string& html);
    std::string cleanHtmlText(const std::string& text);
};

} // namespace CharacterCard
} // namespace AutoCoder

#endif // CHARACTER_CARD_WEB_SCRAPER_H
