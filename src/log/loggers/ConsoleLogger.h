//
// Created by Magnitola on 19.10.2025.
//

#pragma once
#include <string>

#include <log/Logger.h>


class ConsoleLogger final : public Logger {
public:
    ConsoleLogger() = default;

    void log(std::string message) override;
};
