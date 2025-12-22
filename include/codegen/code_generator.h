#ifndef AUTOCODER_CODE_GENERATOR_H
#define AUTOCODER_CODE_GENERATOR_H

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace AutoCoder {
namespace CodeGen {

struct CodeGenerationRequest {
    std::string description;
    std::string language;
    std::string framework;
    std::vector<std::string> requirements;
    std::map<std::string, std::string> options;
};

struct CodeGenerationResult {
    std::string code;
    std::string language;
    std::vector<std::string> dependencies;
    std::vector<std::string> warnings;
    bool success;
    std::string error_message;
};

class CodeGenerator {
public:
    CodeGenerator();
    ~CodeGenerator();

    void initialize();
    void shutdown();

    CodeGenerationResult generate(const CodeGenerationRequest& request);

    std::string generateFunction(
        const std::string& description,
        const std::string& language,
        const std::vector<std::string>& parameters
    );

    std::string generateClass(
        const std::string& class_name,
        const std::string& language,
        const std::vector<std::string>& methods
    );

    std::string generateModule(
        const std::string& module_name,
        const std::string& language,
        const std::vector<std::string>& components
    );

    std::string generateTests(
        const std::string& code,
        const std::string& language
    );

    std::string generateDocumentation(
        const std::string& code,
        const std::string& language
    );

    void setAIClient(void* ai_client);
    void setTemplateDirectory(const std::string& directory);

private:
    std::string buildPrompt(const CodeGenerationRequest& request);
    void validateGeneratedCode(CodeGenerationResult& result);
    void extractDependencies(CodeGenerationResult& result);

    void* ai_client_;
    std::string template_directory_;
};

} // namespace CodeGen
} // namespace AutoCoder

#endif // AUTOCODER_CODE_GENERATOR_H
