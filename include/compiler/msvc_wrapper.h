#ifndef AUTOCODER_MSVC_WRAPPER_H
#define AUTOCODER_MSVC_WRAPPER_H

#include "compiler_interface.h"

namespace AutoCoder {
namespace Compiler {

class MSVCWrapper : public CompilerInterface {
public:
    MSVCWrapper();
    ~MSVCWrapper() override;

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

    void setMSVCPath(const std::string& path);

private:
    std::string buildCommandLine(
        const std::vector<std::string>& sources,
        const std::string& output,
        const CompileOptions& options
    );

    CompileResult executeCompiler(const std::string& command);
    bool findVSInstallation();

    std::string msvc_path_;
    std::string vs_install_path_;
};

} // namespace Compiler
} // namespace AutoCoder

#endif // AUTOCODER_MSVC_WRAPPER_H
