//
// Created by Magnitola on 19.10.2025.
//

#include "Log.h"

#include "Logger.h"

void Log::registerLogger(std::unique_ptr<Logger> logger) {
    loggers_.emplace_back(std::move(logger));
}

void Log::logImpl(const LogLevel level, std::string message, const std::source_location loc) const {
    std::string levelStr = levelToString(level);
    std::string locationStr = formatLocation(loc);

    const std::string formattedMessage = std::format("[{}] {} @ {}",
                                                     levelStr, message, locationStr);

    for (const auto &logger: loggers_) {
        logger->log(formattedMessage);
    }
}

std::string Log::levelToString(const LogLevel level) {
    switch (level) {
        case Info:
            return "INFO";
        case Warning:
            return "WARNING";
        case Error:
            return "ERROR";
        default:
            return "";
    }
}

std::string Log::formatLocation(const std::source_location location) {
    return std::format("{}:{} ({})",
                       location.file_name(),
                       location.line(),
                       location.function_name());
}
