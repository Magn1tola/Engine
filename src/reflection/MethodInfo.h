//
// Created by Magnitola on 15.10.2025.
//

#pragma once
#include <any>
#include <functional>
#include <string>
#include <typeindex>
#include <vector>


class MethodInfo {
public:
    using InvokeFunc = std::function<std::any(void *, std::vector<std::any>)>;

    MethodInfo(std::string name,
               std::type_index returnType,
               const std::vector<std::type_index> &paramTypes,
               InvokeFunc invoker);

    std::any invoke(void *object, const std::vector<std::any> &args) const;

    const std::string &getName() const;

    const std::type_index &getReturnType() const;

    const std::vector<std::type_index> &getParamTypes() const;

private:
    std::string name_;
    std::type_index returnType_;
    std::vector<std::type_index> paramTypes_;
    InvokeFunc invoker_;
};
