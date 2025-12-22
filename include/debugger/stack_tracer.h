#ifndef AUTOCODER_STACK_TRACER_H
#define AUTOCODER_STACK_TRACER_H

#include <string>
#include <vector>
#include <map>

namespace AutoCoder {
namespace Debugger {

struct StackFrame {
    int frame_number;
    std::string function_name;
    std::string file_path;
    int line_number;
    std::map<std::string, std::string> local_variables;
    std::string module_name;
    uintptr_t address;
};

class StackTracer {
public:
    StackTracer();
    ~StackTracer();

    std::vector<StackFrame> captureStackTrace();
    std::vector<StackFrame> captureStackTraceForThread(int thread_id);

    std::string formatStackTrace(const std::vector<StackFrame>& frames);
    void printStackTrace(const std::vector<StackFrame>& frames);

    StackFrame getCurrentFrame();
    std::vector<StackFrame> getCallChain();

    void enableFrameFiltering(bool enable);
    void addFilterPattern(const std::string& pattern);
    void clearFilterPatterns();

private:
    std::vector<StackFrame> parseStackTrace(void* context);
    bool shouldFilterFrame(const StackFrame& frame);
    void resolveSymbols(StackFrame& frame);

    bool frame_filtering_enabled_;
    std::vector<std::string> filter_patterns_;
};

} // namespace Debugger
} // namespace AutoCoder

#endif // AUTOCODER_STACK_TRACER_H
