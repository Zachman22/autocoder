#include "compiler/clang_wrapper.h"
namespace AutoCoder { namespace Compiler {
ClangWrapper::ClangWrapper() : clang_path_("clang"), clangpp_path_("clang++") {}
ClangWrapper::~ClangWrapper() {}
CompileResult ClangWrapper::compile(const std::string& source_file, const std::string& output_file, const CompileOptions& options) { return CompileResult(); }
CompileResult ClangWrapper::compileAndLink(const std::vector<std::string>& source_files, const std::string& output_file, const CompileOptions& options) { return CompileResult(); }
std::string ClangWrapper::getVersion() const { return "Clang"; }
bool ClangWrapper::isAvailable() const { return true; }
CompilerType ClangWrapper::getType() const { return CompilerType::CLANG; }
void ClangWrapper::setClangPath(const std::string& path) { clang_path_ = path; }
void ClangWrapper::setClangPPPath(const std::string& path) { clangpp_path_ = path; }
std::string ClangWrapper::buildCommandLine(const std::vector<std::string>& sources, const std::string& output, const CompileOptions& options) { return ""; }
CompileResult ClangWrapper::executeCompiler(const std::string& command) { return CompileResult(); }
}} // namespace
