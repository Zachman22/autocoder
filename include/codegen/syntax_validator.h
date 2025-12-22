#ifndef AUTOCODER_SYNTAX_VALIDATOR_H
#define AUTOCODER_SYNTAX_VALIDATOR_H

#include <string>
#include <vector>

namespace AutoCoder {
namespace CodeGen {

enum class SyntaxErrorSeverity {
    ERROR,
    WARNING,
    INFO
};

struct SyntaxError {
    SyntaxErrorSeverity severity;
    int line_number;
    int column;
    std::string message;
    std::string suggestion;
};

struct ValidationResult {
    bool is_valid;
    std::vector<SyntaxError> errors;
    std::vector<std::string> suggestions;
    std::string formatted_code;
};

class SyntaxValidator {
public:
    SyntaxValidator();
    ~SyntaxValidator();

    ValidationResult validate(const std::string& code, const std::string& language);

    bool checkSyntax(const std::string& code, const std::string& language);
    std::string formatCode(const std::string& code, const std::string& language);

    void enableAutoFix(bool enable);
    std::string autoFixIssues(const std::string& code, const std::string& language);

    void setStrictMode(bool strict);

private:
    bool validateWithParser(const std::string& code, const std::string& language);
    void runLanguageSpecificChecks(ValidationResult& result, const std::string& language);
    std::string applyFormatting(const std::string& code, const std::string& language);

    bool auto_fix_enabled_;
    bool strict_mode_;
};

} // namespace CodeGen
} // namespace AutoCoder

#endif // AUTOCODER_SYNTAX_VALIDATOR_H
