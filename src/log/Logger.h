//
// Created by Magnitola on 19.10.2025.
//

#pragma once
#include <string>


class Logger {
public:
    Logger() = default;

    virtual ~Logger() = default;

    virtual void log(std::string message) = 0;
};
