//
// Created by Magnitola on 15.10.2025.
//

#include "MethodInfo.h"

#include <utility>

MethodInfo::MethodInfo(std::string name,
                       const std::type_index returnType,
                       const std::vector<std::type_index> &paramTypes,
                       InvokeFunc invoker)
    : name_(std::move(name)), returnType_(returnType), paramTypes_(paramTypes), invoker_(std::move(invoker)) {
}

std::any MethodInfo::invoke(void *object, const std::vector<std::any> &args) const {
    return invoker_(object, args);
}

const std::string &MethodInfo::getName() const {
    return name_;
}

const std::type_index &MethodInfo::getReturnType() const {
    return returnType_;
}

const std::vector<std::type_index> &MethodInfo::getParamTypes() const {
    return paramTypes_;
}
