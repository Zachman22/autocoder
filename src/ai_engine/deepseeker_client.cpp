#include "ai_engine/deepseeker_client.h"
#include <curl/curl.h>
#include <sstream>

namespace AutoCoder {
namespace AIEngine {

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

DeepSeekerClient::DeepSeekerClient()
    : api_endpoint_("https://api.deepseek.com/v1/chat/completions")
    , model_("deepseek-coder")
    , timeout_seconds_(60) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

DeepSeekerClient::~DeepSeekerClient() {
    curl_global_cleanup();
}

void DeepSeekerClient::setApiKey(const std::string& api_key) {
    api_key_ = api_key;
}

void DeepSeekerClient::setApiEndpoint(const std::string& endpoint) {
    api_endpoint_ = endpoint;
}

void DeepSeekerClient::setModel(const std::string& model) {
    model_ = model;
}

CompletionResponse DeepSeekerClient::complete(const CompletionRequest& request) {
    std::string payload = buildPayload(request);
    std::string response = makeRequest(api_endpoint_, payload);
    return parseResponse(response);
}

void DeepSeekerClient::completeAsync(
    const CompletionRequest& request,
    std::function<void(const CompletionResponse&)> callback) {
    // TODO: Implement async completion
    auto response = complete(request);
    callback(response);
}

std::string DeepSeekerClient::generateCode(
    const std::string& prompt,
    const std::string& language) {
    CompletionRequest request;
    request.model = model_;
    request.temperature = 0.7;
    request.max_tokens = 2000;

    Message user_msg;
    user_msg.role = "user";
    user_msg.content = "Generate " + language + " code: " + prompt;
    request.messages.push_back(user_msg);

    auto response = complete(request);
    return response.success ? response.content : "";
}

std::string DeepSeekerClient::improveCode(
    const std::string& code,
    const std::string& improvement_goal) {
    CompletionRequest request;
    request.model = model_;
    request.temperature = 0.5;
    request.max_tokens = 3000;

    Message user_msg;
    user_msg.role = "user";
    user_msg.content = "Improve this code for " + improvement_goal + ":\n\n" + code;
    request.messages.push_back(user_msg);

    auto response = complete(request);
    return response.success ? response.content : "";
}

std::string DeepSeekerClient::debugCode(
    const std::string& code,
    const std::string& error_message) {
    CompletionRequest request;
    request.model = model_;
    request.temperature = 0.3;
    request.max_tokens = 2000;

    Message user_msg;
    user_msg.role = "user";
    user_msg.content = "Fix this code. Error: " + error_message + "\n\nCode:\n" + code;
    request.messages.push_back(user_msg);

    auto response = complete(request);
    return response.success ? response.content : "";
}

bool DeepSeekerClient::testConnection() {
    // TODO: Implement connection test
    return !api_key_.empty();
}

std::string DeepSeekerClient::makeRequest(
    const std::string& endpoint,
    const std::string& payload) {
    CURL* curl = curl_easy_init();
    std::string response_string;

    if (curl) {
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string auth_header = "Authorization: Bearer " + api_key_;
        headers = curl_slist_append(headers, auth_header.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout_seconds_);

        CURLcode res = curl_easy_perform(curl);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            return "{\"error\": \"" + std::string(curl_easy_strerror(res)) + "\"}";
        }
    }

    return response_string;
}

std::string DeepSeekerClient::buildPayload(const CompletionRequest& request) {
    // TODO: Implement proper JSON building
    std::ostringstream oss;
    oss << "{"
        << "\"model\":\"" << request.model << "\","
        << "\"messages\":[";

    for (size_t i = 0; i < request.messages.size(); ++i) {
        const auto& msg = request.messages[i];
        oss << "{\"role\":\"" << msg.role << "\","
            << "\"content\":\"" << msg.content << "\"}";
        if (i < request.messages.size() - 1) {
            oss << ",";
        }
    }

    oss << "],"
        << "\"temperature\":" << request.temperature << ","
        << "\"max_tokens\":" << request.max_tokens
        << "}";

    return oss.str();
}

CompletionResponse DeepSeekerClient::parseResponse(const std::string& response) {
    CompletionResponse result;
    // TODO: Implement proper JSON parsing
    result.success = response.find("error") == std::string::npos;
    result.content = response;
    result.tokens_used = 0;
    return result;
}

} // namespace AIEngine
} // namespace AutoCoder
