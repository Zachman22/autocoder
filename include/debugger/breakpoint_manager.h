#ifndef AUTOCODER_BREAKPOINT_MANAGER_H
#define AUTOCODER_BREAKPOINT_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace AutoCoder {
namespace Debugger {

struct Breakpoint {
    int id;
    std::string file_path;
    int line_number;
    std::string condition;
    bool enabled;
    int hit_count;
    std::function<void()> callback;
};

class BreakpointManager {
public:
    BreakpointManager();
    ~BreakpointManager();

    int addBreakpoint(
        const std::string& file_path,
        int line_number,
        const std::string& condition = ""
    );

    bool removeBreakpoint(int breakpoint_id);
    bool enableBreakpoint(int breakpoint_id);
    bool disableBreakpoint(int breakpoint_id);

    void setBreakpointCondition(int breakpoint_id, const std::string& condition);
    void setBreakpointCallback(int breakpoint_id, std::function<void()> callback);

    Breakpoint* getBreakpoint(int breakpoint_id);
    std::vector<Breakpoint> getAllBreakpoints() const;
    std::vector<Breakpoint> getBreakpointsForFile(const std::string& file_path) const;

    void clearAllBreakpoints();
    void clearBreakpointsForFile(const std::string& file_path);

    bool hasBreakpointAt(const std::string& file_path, int line_number) const;

private:
    std::map<int, Breakpoint> breakpoints_;
    int next_breakpoint_id_;
};

} // namespace Debugger
} // namespace AutoCoder

#endif // AUTOCODER_BREAKPOINT_MANAGER_H
