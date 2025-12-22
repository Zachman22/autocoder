#ifndef AUTOCODER_CLANG_WRAPPER_H
#define AUTOCODER_CLANG_WRAPPER_H

#include "compiler_interface.h"

namespace AutoCoder {
namespace Compiler {

class ClangWrapper : public CompilerInterface {
public:
    ClangWrapper();
    ~ClangWrapper() override;

    CompileResult compile(
        const std::string& source_file,
        const std::string& output_file,
        const CompileOptions& options
    ) override;

    CompileResult compileAndLink(
        const std::vector<std::string>& source_files,
        const std::string& output_file,
        const CompileOptions& options
    ) override;

    std::string getVersion() const override;
    bool isAvailable() const override;
    CompilerType getType() const override;

    void setClangPath(const std::string& path);
    void setClangPPPath(const std::string& path);

private:
    std::string buildCommandLine(
        const std::vector<std::string>& sources,
        const std::string& output,
        const CompileOptions& options
    );

    CompileResult executeCompiler(const std::string& command);

    std::string clang_path_;
    std::string clangpp_path_;
};

} // namespace Compiler
} // namespace AutoCoder

#endif // AUTOCODER_CLANG_WRAPPER_H
