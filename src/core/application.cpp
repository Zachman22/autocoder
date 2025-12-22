#include "core/application.h"
#include "core/config_manager.h"
#include "core/logger.h"
#include "core/plugin_manager.h"
#include "gui/main_window.h"
#include <QApplication>
#include <csignal>
#include <iostream>

namespace AutoCoder {
namespace Core {

Application* Application::instance_ = nullptr;

Application::Application(int argc, char* argv[])
    : initialized_(false) {
    instance_ = this;
    qapp_ = std::make_unique<QApplication>(argc, argv);
    config_manager_ = std::make_unique<ConfigManager>();
    logger_ = std::make_unique<Logger>();
    plugin_manager_ = std::make_unique<PluginManager>();
}

Application::~Application() {
    shutdown();
    instance_ = nullptr;
}

void Application::initialize() {
    if (initialized_) {
        return;
    }

    logger_->info("Initializing AutoCoder...");

    // Load configuration
    config_manager_->loadConfig("config.json");

    // Set up logging
    logger_->setLogFile("autocoder.log");
    logger_->setLogLevel(LogLevel::INFO);

    // Load plugins
    loadPlugins();

    // Setup signal handlers
    setupSignalHandlers();

    initialized_ = true;
    logger_->info("AutoCoder initialized successfully");
}

int Application::run() {
    initialize();

    logger_->info("Starting GUI...");

    GUI::MainWindow main_window;
    main_window.initialize();
    main_window.show();

    return qapp_->exec();
}

void Application::shutdown() {
    if (!initialized_) {
        return;
    }

    logger_->info("Shutting down AutoCoder...");

    plugin_manager_->unloadAllPlugins();
    config_manager_->saveConfig("config.json");

    logger_->info("AutoCoder shutdown complete");
    initialized_ = false;
}

ConfigManager* Application::getConfigManager() const {
    return config_manager_.get();
}

Logger* Application::getLogger() const {
    return logger_.get();
}

PluginManager* Application::getPluginManager() const {
    return plugin_manager_.get();
}

Application* Application::getInstance() {
    return instance_;
}

void Application::loadPlugins() {
    logger_->info("Loading plugins...");
    plugin_manager_->loadAllPlugins("plugins");
}

void Application::setupSignalHandlers() {
    // Setup graceful shutdown on signals
    std::signal(SIGINT, [](int) {
        if (Application::getInstance()) {
            Application::getInstance()->shutdown();
            std::exit(0);
        }
    });

    std::signal(SIGTERM, [](int) {
        if (Application::getInstance()) {
            Application::getInstance()->shutdown();
            std::exit(0);
        }
    });
}

} // namespace Core
} // namespace AutoCoder
