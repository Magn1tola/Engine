//
// Created by Magnitola on 15.10.2025.
//

#pragma once
#include <any>
#include <functional>
#include <string>
#include <vector>


class ConstructorInfo {
public:
    using ConstructorFunc = std::function<void*(std::vector<std::any>)>;

    ConstructorInfo(const std::vector<std::string> &paramTypes,
                    ConstructorFunc constructor
    );

    [[nodiscard]] void *construct(const std::vector<std::any> &args) const;

    [[nodiscard]] const std::vector<std::string> &getParamTypes() const;

private:
    std::vector<std::string> paramTypes_;
    ConstructorFunc constructor_;
};
