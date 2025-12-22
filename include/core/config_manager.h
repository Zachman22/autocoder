#ifndef AUTOCODER_CONFIG_MANAGER_H
#define AUTOCODER_CONFIG_MANAGER_H

#include <string>
#include <map>
#include <variant>
#include <mutex>

namespace AutoCoder {
namespace Core {

using ConfigValue = std::variant<std::string, int, double, bool>;

class ConfigManager {
public:
    ConfigManager();
    ~ConfigManager();

    bool loadConfig(const std::string& filepath);
    bool saveConfig(const std::string& filepath);

    template<typename T>
    T get(const std::string& key, const T& default_value = T{}) const;

    template<typename T>
    void set(const std::string& key, const T& value);

    bool has(const std::string& key) const;
    void remove(const std::string& key);
    void clear();

private:
    std::map<std::string, ConfigValue> config_;
    mutable std::mutex mutex_;
    std::string config_file_;
};

} // namespace Core
} // namespace AutoCoder

#endif // AUTOCODER_CONFIG_MANAGER_H
