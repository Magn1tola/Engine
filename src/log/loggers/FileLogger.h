//
// Created by Magnitola on 19.10.2025.
//

#pragma once

#include <fstream>

#include <log/Logger.h>


class FileLogger final : public Logger {
public:
    FileLogger();

    ~FileLogger() override;

    void log(std::string message) override;

private:
    std::ofstream file_;

    static std::string getTimeStamp();
};
