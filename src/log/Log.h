//
// Created by Magnitola on 19.10.2025.
//

#pragma once
#include <format>
#include <memory>
#include <source_location>
#include <vector>

#include "Logger.h"
#include "utils/Singleton.h"

enum LogLevel {
    Info, Warning, Error
};

class Log : public Singleton<Log> {
public:
    template<typename... Args>
    void log(LogLevel level,
             const std::source_location loc,
             std::format_string<Args...> format,
             Args &&... args) {
        auto message = std::format(format, std::forward<Args>(args)...);
        logImpl(level, message, loc);
    }

    void registerLogger(std::unique_ptr<Logger> logger);

private:
    std::vector<std::unique_ptr<Logger> > loggers_;

    void logImpl(LogLevel level, std::string message, std::source_location loc) const;

    static std::string levelToString(LogLevel level);

    static std::string formatLocation(std::source_location location);
};

#define LOG(...) Log::getInstance().log(LogLevel::Info, std::source_location::current(), __VA_ARGS__)
#define LOGW(...) Log::getInstance().log(LogLevel::Warning, std::source_location::current(), __VA_ARGS__)
#define LOGE(...) Log::getInstance().log(LogLevel::Error, std::source_location::current(), __VA_ARGS__)

#define LOG_IF(condition, ...) if (condition) LOG(__VA_ARGS__)
#define LOGW_IF(condition, ...) if (condition) LOGW(__VA_ARGS__)
#define LOGE_IF(condition, ...) if (condition) LOGE(__VA_ARGS__)
