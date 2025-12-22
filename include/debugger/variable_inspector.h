#ifndef AUTOCODER_VARIABLE_INSPECTOR_H
#define AUTOCODER_VARIABLE_INSPECTOR_H

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace AutoCoder {
namespace Debugger {

enum class VariableType {
    INTEGER,
    FLOAT,
    STRING,
    BOOLEAN,
    ARRAY,
    OBJECT,
    POINTER,
    UNKNOWN
};

struct Variable {
    std::string name;
    VariableType type;
    std::string value;
    std::string type_name;
    size_t memory_address;
    size_t size_bytes;
    std::vector<Variable> children;
    bool is_const;
    bool is_reference;
};

class VariableInspector {
public:
    VariableInspector();
    ~VariableInspector();

    Variable inspectVariable(const std::string& variable_name);
    std::vector<Variable> inspectScope();
    std::vector<Variable> inspectGlobalScope();

    std::string getVariableValue(const std::string& variable_name);
    bool setVariableValue(const std::string& variable_name, const std::string& value);

    void watchVariable(const std::string& variable_name);
    void unwatchVariable(const std::string& variable_name);
    std::vector<Variable> getWatchedVariables();

    std::vector<std::string> detectMemoryLeaks();
    std::map<std::string, size_t> getMemoryUsage();

    void enableChangeTracking(bool enable);
    std::vector<std::string> getModifiedVariables();

private:
    void parseVariableType(Variable& var);
    void expandComplexVariable(Variable& var);
    bool trackVariableChanges(const std::string& variable_name);

    std::vector<std::string> watched_variables_;
    std::map<std::string, std::string> variable_history_;
    bool change_tracking_enabled_;
};

} // namespace Debugger
} // namespace AutoCoder

#endif // AUTOCODER_VARIABLE_INSPECTOR_H
