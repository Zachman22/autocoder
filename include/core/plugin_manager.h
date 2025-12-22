#ifndef AUTOCODER_PLUGIN_MANAGER_H
#define AUTOCODER_PLUGIN_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace AutoCoder {
namespace Core {

class Plugin {
public:
    virtual ~Plugin() = default;
    virtual std::string getName() const = 0;
    virtual std::string getVersion() const = 0;
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
};

class PluginManager {
public:
    PluginManager();
    ~PluginManager();

    bool loadPlugin(const std::string& plugin_path);
    bool unloadPlugin(const std::string& plugin_name);

    Plugin* getPlugin(const std::string& plugin_name);
    std::vector<std::string> getLoadedPlugins() const;

    void loadAllPlugins(const std::string& plugins_directory);
    void unloadAllPlugins();

private:
    std::map<std::string, std::shared_ptr<Plugin>> plugins_;
    std::map<std::string, void*> plugin_handles_;
};

} // namespace Core
} // namespace AutoCoder

#endif // AUTOCODER_PLUGIN_MANAGER_H
