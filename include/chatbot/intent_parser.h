#ifndef AUTOCODER_INTENT_PARSER_H
#define AUTOCODER_INTENT_PARSER_H

#include <string>
#include <vector>
#include <map>

namespace AutoCoder {
namespace Chatbot {

enum class Intent {
    CODE_GENERATION,
    CODE_EXPLANATION,
    DEBUG_HELP,
    REFACTORING,
    DOCUMENTATION,
    TESTING,
    OPTIMIZATION,
    QUESTION,
    GENERAL_CHAT,
    UNKNOWN
};

struct ParsedIntent {
    Intent primary_intent;
    std::vector<Intent> secondary_intents;
    std::string language;
    std::map<std::string, std::string> parameters;
    double confidence;
};

class IntentParser {
public:
    IntentParser();
    ~IntentParser();

    ParsedIntent parse(const std::string& user_input);
    std::vector<ParsedIntent> parseMultiple(const std::string& user_input);

    void trainOnData(const std::vector<std::pair<std::string, Intent>>& training_data);
    void loadModel(const std::string& model_path);
    void saveModel(const std::string& model_path);

    std::string intentToString(Intent intent) const;
    Intent stringToIntent(const std::string& intent_str) const;

private:
    Intent classifyIntent(const std::string& input);
    std::string extractLanguage(const std::string& input);
    std::map<std::string, std::string> extractParameters(const std::string& input);
    double calculateConfidence(const std::string& input, Intent intent);

    std::map<std::string, Intent> keyword_map_;
    std::vector<std::string> language_keywords_;
};

} // namespace Chatbot
} // namespace AutoCoder

#endif // AUTOCODER_INTENT_PARSER_H
