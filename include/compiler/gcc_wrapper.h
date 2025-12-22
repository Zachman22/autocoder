#ifndef AUTOCODER_GCC_WRAPPER_H
#define AUTOCODER_GCC_WRAPPER_H

#include "compiler_interface.h"

namespace AutoCoder {
namespace Compiler {

class GCCWrapper : public CompilerInterface {
public:
    GCCWrapper();
    ~GCCWrapper() override;

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

    void setGCCPath(const std::string& path);
    void setGPPPath(const std::string& path);

private:
    std::string buildCommandLine(
        const std::vector<std::string>& sources,
        const std::string& output,
        const CompileOptions& options
    );

    CompileResult executeCompiler(const std::string& command);

    std::string gcc_path_;
    std::string gpp_path_;
};

} // namespace Compiler
} // namespace AutoCoder

#endif // AUTOCODER_GCC_WRAPPER_H
