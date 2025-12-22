#ifndef AUTOCODER_COMPILER_INTERFACE_H
#define AUTOCODER_COMPILER_INTERFACE_H

#include <string>
#include <vector>
#include <map>

namespace AutoCoder {
namespace Compiler {

enum class CompilerType {
    GCC,
    CLANG,
    MSVC,
    MINGW,
    CUSTOM
};

enum class OptimizationLevel {
    NONE,
    O1,
    O2,
    O3,
    OS,
    OFAST
};

struct CompileOptions {
    CompilerType compiler;
    OptimizationLevel optimization;
    std::string standard;
    std::vector<std::string> include_paths;
    std::vector<std::string> library_paths;
    std::vector<std::string> libraries;
    std::vector<std::string> defines;
    std::vector<std::string> flags;
    bool debug_symbols;
    bool warnings_as_errors;
    int warning_level;
};

struct CompileResult {
    bool success;
    std::string output_file;
    std::string stdout_output;
    std::string stderr_output;
    int exit_code;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    double compile_time_seconds;
};

class CompilerInterface {
public:
    virtual ~CompilerInterface() = default;

    virtual CompileResult compile(
        const std::string& source_file,
        const std::string& output_file,
        const CompileOptions& options
    ) = 0;

    virtual CompileResult compileAndLink(
        const std::vector<std::string>& source_files,
        const std::string& output_file,
        const CompileOptions& options
    ) = 0;

    virtual std::string getVersion() const = 0;
    virtual bool isAvailable() const = 0;
    virtual CompilerType getType() const = 0;
};

} // namespace Compiler
} // namespace AutoCoder

#endif // AUTOCODER_COMPILER_INTERFACE_H
