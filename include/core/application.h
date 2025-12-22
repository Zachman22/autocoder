#ifndef AUTOCODER_APPLICATION_H
#define AUTOCODER_APPLICATION_H

#include <memory>
#include <string>
#include <QApplication>

namespace AutoCoder {
namespace Core {

class ConfigManager;
class Logger;
class PluginManager;

class Application {
public:
    Application(int argc, char* argv[]);
    ~Application();

    int run();
    void shutdown();

    ConfigManager* getConfigManager() const;
    Logger* getLogger() const;
    PluginManager* getPluginManager() const;

    static Application* getInstance();

private:
    void initialize();
    void loadPlugins();
    void setupSignalHandlers();

    static Application* instance_;
    std::unique_ptr<QApplication> qapp_;
    std::unique_ptr<ConfigManager> config_manager_;
    std::unique_ptr<Logger> logger_;
    std::unique_ptr<PluginManager> plugin_manager_;
    bool initialized_;
};

} // namespace Core
} // namespace AutoCoder

#endif // AUTOCODER_APPLICATION_H
