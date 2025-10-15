//
// Created by Magnitola on 15.10.2025.
//

#pragma once
#include <any>
#include <functional>
#include <string>
#include <vector>


class MethodInfo {
public:
    using InvokeFunc = std::function<std::any(void *, std::vector<std::any>)>;

    MethodInfo(const std::string &name,
               const std::string &returnType,
               const std::vector<std::string> &paramTypes,
               InvokeFunc invoker);

    std::any invoke(void *object, const std::vector<std::any> &args) const;

    const std::string &getName() const;

    const std::string &getReturnType() const;

    const std::vector<std::string> &getParamTypes() const;

private:
    std::string name_;
    std::string returnType_;
    std::vector<std::string> paramTypes_;
    InvokeFunc invoker_;
};
