#ifndef AUTOCODER_CHAT_INTERFACE_H
#define AUTOCODER_CHAT_INTERFACE_H

#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace AutoCoder {
namespace Chatbot {

struct ChatMessage {
    std::string role;
    std::string content;
    std::string timestamp;
    std::string message_id;
};

struct ChatContext {
    std::vector<ChatMessage> history;
    std::string current_project;
    std::string current_language;
    std::map<std::string, std::string> metadata;
};

using MessageCallback = std::function<void(const ChatMessage&)>;

class ChatInterface {
public:
    ChatInterface();
    ~ChatInterface();

    void initialize();
    void shutdown();

    std::string sendMessage(const std::string& message);
    void sendMessageAsync(const std::string& message, MessageCallback callback);

    void clearHistory();
    std::vector<ChatMessage> getHistory() const;
    void setContext(const ChatContext& context);
    ChatContext getContext() const;

    void setSystemPrompt(const std::string& prompt);
    void setPersonality(const std::string& personality_name);

    void enableCodeGeneration(bool enable);
    void enableDebugAssistance(bool enable);
    void enableExplanations(bool enable);

private:
    std::string processUserInput(const std::string& input);
    std::string generateResponse(const std::string& processed_input);
    void updateContext(const ChatMessage& message);

    ChatContext context_;
    std::string system_prompt_;
    bool code_generation_enabled_;
    bool debug_assistance_enabled_;
    bool explanations_enabled_;
};

} // namespace Chatbot
} // namespace AutoCoder

#endif // AUTOCODER_CHAT_INTERFACE_H
