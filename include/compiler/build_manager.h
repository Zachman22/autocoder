#ifndef AUTOCODER_BUILD_MANAGER_H
#define AUTOCODER_BUILD_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include "compiler_interface.h"

namespace AutoCoder {
namespace Compiler {

struct BuildConfiguration {
    std::string name;
    CompilerType compiler;
    std::vector<std::string> source_files;
    std::string output_directory;
    std::string output_name;
    CompileOptions options;
};

struct BuildResult {
    bool success;
    std::vector<CompileResult> compile_results;
    std::string executable_path;
    double total_build_time;
};

using BuildProgressCallback = std::function<void(int current, int total, const std::string& file)>;

class BuildManager {
public:
    BuildManager();
    ~BuildManager();

    void setCompiler(CompilerType type);
    CompilerInterface* getCompiler(CompilerType type);

    BuildResult build(const BuildConfiguration& config);
    BuildResult buildParallel(const BuildConfiguration& config, int num_threads);

    void setBuildProgressCallback(BuildProgressCallback callback);

    bool clean(const std::string& output_directory);
    bool rebuild(const BuildConfiguration& config);

    void enableIncrementalBuild(bool enable);
    void enableCaching(bool enable);

    std::vector<std::string> findSourceFiles(
        const std::string& directory,
        const std::vector<std::string>& extensions
    );

    bool generateMakefile(const BuildConfiguration& config, const std::string& output_path);
    bool generateCMakeLists(const BuildConfiguration& config, const std::string& output_path);

private:
    std::vector<std::string> determineCompilationOrder(const std::vector<std::string>& sources);
    bool isUpToDate(const std::string& source, const std::string& object);

    std::map<CompilerType, std::unique_ptr<CompilerInterface>> compilers_;
    BuildProgressCallback progress_callback_;
    bool incremental_build_;
    bool caching_enabled_;
    std::map<std::string, time_t> file_timestamps_;
};

} // namespace Compiler
} // namespace AutoCoder

#endif // AUTOCODER_BUILD_MANAGER_H
