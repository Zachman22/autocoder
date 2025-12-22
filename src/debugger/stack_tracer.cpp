#include "debugger/stack_tracer.h"

namespace AutoCoder {
namespace Debugger {

StackTracer::StackTracer() : frame_filtering_enabled_(false) {}
StackTracer::~StackTracer() {}
std::vector<StackFrame> StackTracer::captureStackTrace() { return {}; }
std::vector<StackFrame> StackTracer::captureStackTraceForThread(int thread_id) { return {}; }
std::string StackTracer::formatStackTrace(const std::vector<StackFrame>& frames) { return ""; }
void StackTracer::printStackTrace(const std::vector<StackFrame>& frames) {}
StackFrame StackTracer::getCurrentFrame() { return StackFrame(); }
std::vector<StackFrame> StackTracer::getCallChain() { return {}; }
void StackTracer::enableFrameFiltering(bool enable) { frame_filtering_enabled_ = enable; }
void StackTracer::addFilterPattern(const std::string& pattern) { filter_patterns_.push_back(pattern); }
void StackTracer::clearFilterPatterns() { filter_patterns_.clear(); }
std::vector<StackFrame> StackTracer::parseStackTrace(void* context) { return {}; }
bool StackTracer::shouldFilterFrame(const StackFrame& frame) { return false; }
void StackTracer::resolveSymbols(StackFrame& frame) {}

} // namespace Debugger
} // namespace AutoCoder
