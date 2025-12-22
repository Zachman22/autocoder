#ifndef AUTOCODER_MULTI_LANGUAGE_SUPPORT_H
#define AUTOCODER_MULTI_LANGUAGE_SUPPORT_H

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace AutoCoder {
namespace CodeGen {

class LanguageHandler {
public:
    virtual ~LanguageHandler() = default;
    virtual std::string getName() const = 0;
    virtual std::string formatCode(const std::string& code) = 0;
    virtual bool validateSyntax(const std::string& code) = 0;
    virtual std::string generateBoilerplate(const std::string& template_name) = 0;
    virtual std::vector<std::string> getSupportedFeatures() const = 0;
};

class MultiLanguageSupport {
public:
    MultiLanguageSupport();
    ~MultiLanguageSupport();

    void registerLanguage(const std::string& language, std::shared_ptr<LanguageHandler> handler);
    void unregisterLanguage(const std::string& language);

    LanguageHandler* getHandler(const std::string& language);
    std::vector<std::string> getSupportedLanguages() const;

    std::string transpile(
        const std::string& code,
        const std::string& from_language,
        const std::string& to_language
    );

    std::map<std::string, std::string> generateMultiLanguageCode(
        const std::string& description,
        const std::vector<std::string>& target_languages
    );

    bool isLanguageSupported(const std::string& language) const;

private:
    void loadDefaultLanguages();

    std::map<std::string, std::shared_ptr<LanguageHandler>> handlers_;
};

// Specific language handlers
class PythonHandler : public LanguageHandler {
public:
    std::string getName() const override;
    std::string formatCode(const std::string& code) override;
    bool validateSyntax(const std::string& code) override;
    std::string generateBoilerplate(const std::string& template_name) override;
    std::vector<std::string> getSupportedFeatures() const override;
};

class JavaScriptHandler : public LanguageHandler {
public:
    std::string getName() const override;
    std::string formatCode(const std::string& code) override;
    bool validateSyntax(const std::string& code) override;
    std::string generateBoilerplate(const std::string& template_name) override;
    std::vector<std::string> getSupportedFeatures() const override;
};

class CppHandler : public LanguageHandler {
public:
    std::string getName() const override;
    std::string formatCode(const std::string& code) override;
    bool validateSyntax(const std::string& code) override;
    std::string generateBoilerplate(const std::string& template_name) override;
    std::vector<std::string> getSupportedFeatures() const override;
};

} // namespace CodeGen
} // namespace AutoCoder

#endif // AUTOCODER_MULTI_LANGUAGE_SUPPORT_H
