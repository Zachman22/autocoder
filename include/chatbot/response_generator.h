#ifndef AUTOCODER_RESPONSE_GENERATOR_H
#define AUTOCODER_RESPONSE_GENERATOR_H

#include <string>
#include <vector>
#include <map>
#include "intent_parser.h"

namespace AutoCoder {
namespace Chatbot {

struct ResponseTemplate {
    Intent intent;
    std::vector<std::string> templates;
    std::map<std::string, std::string> variables;
};

class ResponseGenerator {
public:
    ResponseGenerator();
    ~ResponseGenerator();

    std::string generate(const ParsedIntent& intent, const std::string& context);

    void addTemplate(const ResponseTemplate& template_def);
    void loadTemplates(const std::string& templates_file);
    void saveTemplates(const std::string& templates_file);

    void setResponseStyle(const std::string& style);
    void setVerbosity(int level);

    std::string formatCodeBlock(const std::string& code, const std::string& language);
    std::string formatList(const std::vector<std::string>& items);
    std::string formatTable(const std::vector<std::vector<std::string>>& data);

private:
    std::string selectTemplate(Intent intent);
    std::string fillTemplate(const std::string& template_str, const std::map<std::string, std::string>& vars);
    std::string enhanceResponse(const std::string& response);

    std::map<Intent, std::vector<std::string>> templates_;
    std::string response_style_;
    int verbosity_level_;
};

} // namespace Chatbot
} // namespace AutoCoder

#endif // AUTOCODER_RESPONSE_GENERATOR_H
