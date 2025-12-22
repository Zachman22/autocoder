#ifndef AUTOCODER_DEEPSEEKER_CLIENT_H
#define AUTOCODER_DEEPSEEKER_CLIENT_H

#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace AutoCoder {
namespace AIEngine {

struct Message {
    std::string role;
    std::string content;
};

struct CompletionRequest {
    std::string model;
    std::vector<Message> messages;
    double temperature;
    int max_tokens;
    double top_p;
    std::string stop;
};

struct CompletionResponse {
    std::string id;
    std::string model;
    std::string content;
    int tokens_used;
    bool success;
    std::string error_message;
};

class DeepSeekerClient {
public:
    DeepSeekerClient();
    ~DeepSeekerClient();

    void setApiKey(const std::string& api_key);
    void setApiEndpoint(const std::string& endpoint);
    void setModel(const std::string& model);

    CompletionResponse complete(const CompletionRequest& request);

    void completeAsync(
        const CompletionRequest& request,
        std::function<void(const CompletionResponse&)> callback
    );

    std::string generateCode(
        const std::string& prompt,
        const std::string& language = ""
    );

    std::string improveCode(
        const std::string& code,
        const std::string& improvement_goal
    );

    std::string debugCode(
        const std::string& code,
        const std::string& error_message
    );

    bool testConnection();

private:
    std::string makeRequest(
        const std::string& endpoint,
        const std::string& payload
    );

    std::string buildPayload(const CompletionRequest& request);
    CompletionResponse parseResponse(const std::string& response);

    std::string api_key_;
    std::string api_endpoint_;
    std::string model_;
    int timeout_seconds_;
};

} // namespace AIEngine
} // namespace AutoCoder

#endif // AUTOCODER_DEEPSEEKER_CLIENT_H
