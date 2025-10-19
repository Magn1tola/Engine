//
// Created by Magnitola on 19.10.2025.
//

#include "FileLogger.h"

#include <chrono>

FileLogger::FileLogger() {
    file_ = std::ofstream("log.txt");
}

FileLogger::~FileLogger() {
    if (file_.is_open())
        file_.close();
}

void FileLogger::log(const std::string message) {
    file_ << getTimeStamp() << " " << message << std::endl;
}

std::string FileLogger::getTimeStamp() {
    auto now = std::chrono::system_clock::now();
    return std::format("{:%d-%m-%Y %H:%M:%S}", now);
}
