#ifndef AUTOCODER_CONTINUOUS_DEBUGGER_H
#define AUTOCODER_CONTINUOUS_DEBUGGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <thread>
#include <atomic>

namespace AutoCoder {
namespace Debugger {

enum class DebugEvent {
    BREAKPOINT_HIT,
    EXCEPTION_THROWN,
    VARIABLE_CHANGED,
    FUNCTION_ENTERED,
    FUNCTION_EXITED,
    ERROR_DETECTED,
    WARNING_DETECTED
};

struct DebugEventData {
    DebugEvent type;
    std::string file_path;
    int line_number;
    std::string function_name;
    std::string message;
    std::map<std::string, std::string> variables;
    std::string stack_trace;
};

using DebugEventCallback = std::function<void(const DebugEventData&)>;

class ContinuousDebugger {
public:
    ContinuousDebugger();
    ~ContinuousDebugger();

    void start();
    void stop();
    void pause();
    void resume();

    bool isRunning() const;
    bool isPaused() const;

    void attachToProcess(int pid);
    void detachFromProcess();

    void monitorFile(const std::string& filepath);
    void unmonitorFile(const std::string& filepath);

    void registerEventCallback(DebugEvent event, DebugEventCallback callback);
    void unregisterEventCallback(DebugEvent event);

    void enableAutoFix(bool enable);
    void setScanInterval(int milliseconds);

    std::vector<DebugEventData> getRecentEvents(int count = 100);
    void clearEventHistory();

private:
    void debugLoop();
    void scanForIssues();
    void analyzeCode(const std::string& code, const std::string& filepath);
    void attemptAutoFix(const DebugEventData& event);

    std::atomic<bool> running_;
    std::atomic<bool> paused_;
    std::unique_ptr<std::thread> debug_thread_;

    std::vector<std::string> monitored_files_;
    std::map<DebugEvent, DebugEventCallback> event_callbacks_;
    std::vector<DebugEventData> event_history_;

    int scan_interval_ms_;
    bool auto_fix_enabled_;
    int attached_pid_;
};

} // namespace Debugger
} // namespace AutoCoder

#endif // AUTOCODER_CONTINUOUS_DEBUGGER_H
