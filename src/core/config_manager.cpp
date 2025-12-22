#include "core/config_manager.h"
#include <fstream>
#include <stdexcept>

namespace AutoCoder {
namespace Core {

ConfigManager::ConfigManager() {}

ConfigManager::~ConfigManager() {}

bool ConfigManager::loadConfig(const std::string& filepath) {
    std::lock_guard<std::mutex> lock(mutex_);
    config_file_ = filepath;

    // TODO: Implement JSON parsing
    // For now, set some default values
    config_["theme"] = std::string("dark");
    config_["font_size"] = 12;
    config_["auto_save"] = true;
    config_["api_endpoint"] = std::string("https://api.deepseek.com/v1");
    config_["model"] = std::string("deepseeker-6.7b");

    return true;
}

bool ConfigManager::saveConfig(const std::string& filepath) {
    std::lock_guard<std::mutex> lock(mutex_);

    // TODO: Implement JSON serialization
    return true;
}

bool ConfigManager::has(const std::string& key) const {
    std::lock_guard<std::mutex> lock(mutex_);
    return config_.find(key) != config_.end();
}

void ConfigManager::remove(const std::string& key) {
    std::lock_guard<std::mutex> lock(mutex_);
    config_.erase(key);
}

void ConfigManager::clear() {
    std::lock_guard<std::mutex> lock(mutex_);
    config_.clear();
}

// Template specializations
template<>
std::string ConfigManager::get<std::string>(const std::string& key, const std::string& default_value) const {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = config_.find(key);
    if (it != config_.end() && std::holds_alternative<std::string>(it->second)) {
        return std::get<std::string>(it->second);
    }
    return default_value;
}

template<>
int ConfigManager::get<int>(const std::string& key, const int& default_value) const {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = config_.find(key);
    if (it != config_.end() && std::holds_alternative<int>(it->second)) {
        return std::get<int>(it->second);
    }
    return default_value;
}

template<>
bool ConfigManager::get<bool>(const std::string& key, const bool& default_value) const {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = config_.find(key);
    if (it != config_.end() && std::holds_alternative<bool>(it->second)) {
        return std::get<bool>(it->second);
    }
    return default_value;
}

template<>
void ConfigManager::set<std::string>(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    config_[key] = value;
}

template<>
void ConfigManager::set<int>(const std::string& key, const int& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    config_[key] = value;
}

template<>
void ConfigManager::set<bool>(const std::string& key, const bool& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    config_[key] = value;
}

} // namespace Core
} // namespace AutoCoder
