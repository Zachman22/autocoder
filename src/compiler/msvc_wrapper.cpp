#include "compiler/msvc_wrapper.h"
namespace AutoCoder { namespace Compiler {
MSVCWrapper::MSVCWrapper() {}
MSVCWrapper::~MSVCWrapper() {}
CompileResult MSVCWrapper::compile(const std::string& source_file, const std::string& output_file, const CompileOptions& options) { return CompileResult(); }
CompileResult MSVCWrapper::compileAndLink(const std::vector<std::string>& source_files, const std::string& output_file, const CompileOptions& options) { return CompileResult(); }
std::string MSVCWrapper::getVersion() const { return "MSVC"; }
bool MSVCWrapper::isAvailable() const { return false; }
CompilerType MSVCWrapper::getType() const { return CompilerType::MSVC; }
void MSVCWrapper::setMSVCPath(const std::string& path) { msvc_path_ = path; }
std::string MSVCWrapper::buildCommandLine(const std::vector<std::string>& sources, const std::string& output, const CompileOptions& options) { return ""; }
CompileResult MSVCWrapper::executeCompiler(const std::string& command) { return CompileResult(); }
bool MSVCWrapper::findVSInstallation() { return false; }
}} // namespace
