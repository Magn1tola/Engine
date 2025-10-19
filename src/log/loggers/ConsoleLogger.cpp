//
// Created by Magnitola on 19.10.2025.
//

#include "ConsoleLogger.h"

#include <iostream>
#include <ostream>

void ConsoleLogger::log(const std::string message) {
    std::cout << message << std::endl;
}
