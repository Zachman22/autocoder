#include "core/logger.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

namespace AutoCoder {
namespace Core {

Logger::Logger()
    : current_level_(LogLevel::INFO)
    , console_output_(true)
    , file_output_(false) {}

Logger::~Logger() {
    if (log_file_.is_open()) {
        log_file_.close();
    }
}

void Logger::setLogLevel(LogLevel level) {
    current_level_ = level;
}

void Logger::setLogFile(const std::string& filepath) {
    std::lock_guard<std::mutex> lock(mutex_);

    if (log_file_.is_open()) {
        log_file_.close();
    }

    log_file_.open(filepath, std::ios::app);
    file_output_ = log_file_.is_open();
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::critical(const std::string& message) {
    log(LogLevel::CRITICAL, message);
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < current_level_) {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    std::string formatted = formatMessage(level, message);

    if (console_output_) {
        if (level >= LogLevel::ERROR) {
            std::cerr << formatted << std::endl;
        } else {
            std::cout << formatted << std::endl;
        }
    }

    if (file_output_ && log_file_.is_open()) {
        log_file_ << formatted << std::endl;
        log_file_.flush();
    }
}

std::string Logger::formatMessage(LogLevel level, const std::string& message) {
    std::string timestamp = getCurrentTimestamp();
    std::string level_str = levelToString(level);
    return "[" + timestamp + "] [" + level_str + "] " + message;
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:    return "DEBUG";
        case LogLevel::INFO:     return "INFO";
        case LogLevel::WARNING:  return "WARNING";
        case LogLevel::ERROR:    return "ERROR";
        case LogLevel::CRITICAL: return "CRITICAL";
        default:                 return "UNKNOWN";
    }
}

std::string Logger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_tm = *std::localtime(&now_time_t);

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

} // namespace Core
} // namespace AutoCoder
