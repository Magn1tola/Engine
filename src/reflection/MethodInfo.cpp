//
// Created by Magnitola on 15.10.2025.
//

#include "MethodInfo.h"

MethodInfo::MethodInfo(const std::string &name,
                       const std::string &returnType,
                       const std::vector<std::string> &paramTypes,
                       InvokeFunc invoker)
    : name_(name), returnType_(returnType), paramTypes_(paramTypes), invoker_(std::move(invoker)) {
}

std::any MethodInfo::invoke(void *object, const std::vector<std::any> &args) const {
    return invoker_(object, args);
}

const std::string &MethodInfo::getName() const {
    return name_;
}

const std::string &MethodInfo::getReturnType() const {
    return returnType_;
}

const std::vector<std::string> &MethodInfo::getParamTypes() const {
    return paramTypes_;
}
