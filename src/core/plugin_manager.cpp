#include "core/plugin_manager.h"
#include <filesystem>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

namespace AutoCoder {
namespace Core {

// Platform-specific DLL loading helpers
#ifdef _WIN32
static void* platformLoadLibrary(const char* path) {
    return (void*)LoadLibraryA(path);
}

static void platformUnloadLibrary(void* handle) {
    if (handle) {
        FreeLibrary((HMODULE)handle);
    }
}
#else
static void* platformLoadLibrary(const char* path) {
    return dlopen(path, RTLD_LAZY);
}

static void platformUnloadLibrary(void* handle) {
    if (handle) {
        dlclose(handle);
    }
}
#endif

PluginManager::PluginManager() {}

PluginManager::~PluginManager() {
    unloadAllPlugins();
}

bool PluginManager::loadPlugin(const std::string& plugin_path) {
    void* handle = platformLoadLibrary(plugin_path.c_str());
    if (!handle) {
        return false;
    }

    // TODO: Load plugin initialization function and create plugin instance
    // For now, just store the handle
    return true;
}

bool PluginManager::unloadPlugin(const std::string& plugin_name) {
    auto it = plugin_handles_.find(plugin_name);
    if (it == plugin_handles_.end()) {
        return false;
    }

    platformUnloadLibrary(it->second);

    plugins_.erase(plugin_name);
    plugin_handles_.erase(it);
    return true;
}

Plugin* PluginManager::getPlugin(const std::string& plugin_name) {
    auto it = plugins_.find(plugin_name);
    if (it != plugins_.end()) {
        return it->second.get();
    }
    return nullptr;
}

std::vector<std::string> PluginManager::getLoadedPlugins() const {
    std::vector<std::string> names;
    for (const auto& pair : plugins_) {
        names.push_back(pair.first);
    }
    return names;
}

void PluginManager::loadAllPlugins(const std::string& plugins_directory) {
    // TODO: Scan directory and load all plugins
    // For now, this is a stub
}

void PluginManager::unloadAllPlugins() {
    for (auto& pair : plugin_handles_) {
        platformUnloadLibrary(pair.second);
    }
    plugins_.clear();
    plugin_handles_.clear();
}

} // namespace Core
} // namespace AutoCoder
