#ifndef AUTOCODER_LOGGER_H
#define AUTOCODER_LOGGER_H

#include <string>
#include <fstream>
#include <mutex>
#include <memory>

namespace AutoCoder {
namespace Core {

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger {
public:
    Logger();
    ~Logger();

    void setLogLevel(LogLevel level);
    void setLogFile(const std::string& filepath);

    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);

    void log(LogLevel level, const std::string& message);

private:
    std::string formatMessage(LogLevel level, const std::string& message);
    std::string levelToString(LogLevel level);
    std::string getCurrentTimestamp();

    LogLevel current_level_;
    std::ofstream log_file_;
    std::mutex mutex_;
    bool console_output_;
    bool file_output_;
};

} // namespace Core
} // namespace AutoCoder

#endif // AUTOCODER_LOGGER_H
