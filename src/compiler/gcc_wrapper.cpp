#include "compiler/gcc_wrapper.h"
namespace AutoCoder { namespace Compiler {
GCCWrapper::GCCWrapper() : gcc_path_("gcc"), gpp_path_("g++") {}
GCCWrapper::~GCCWrapper() {}
CompileResult GCCWrapper::compile(const std::string& source_file, const std::string& output_file, const CompileOptions& options) { return CompileResult(); }
CompileResult GCCWrapper::compileAndLink(const std::vector<std::string>& source_files, const std::string& output_file, const CompileOptions& options) { return CompileResult(); }
std::string GCCWrapper::getVersion() const { return "GCC"; }
bool GCCWrapper::isAvailable() const { return true; }
CompilerType GCCWrapper::getType() const { return CompilerType::GCC; }
void GCCWrapper::setGCCPath(const std::string& path) { gcc_path_ = path; }
void GCCWrapper::setGPPPath(const std::string& path) { gpp_path_ = path; }
std::string GCCWrapper::buildCommandLine(const std::vector<std::string>& sources, const std::string& output, const CompileOptions& options) { return ""; }
CompileResult GCCWrapper::executeCompiler(const std::string& command) { return CompileResult(); }
}} // namespace
