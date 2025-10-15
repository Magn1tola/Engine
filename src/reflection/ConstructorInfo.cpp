//
// Created by Magnitola on 15.10.2025.
//

#include "ConstructorInfo.h"

ConstructorInfo::ConstructorInfo(const std::vector<std::string> &paramTypes,
                                 ConstructorFunc constructor)
    : paramTypes_(paramTypes), constructor_(std::move(constructor)) {
}

void *ConstructorInfo::construct(const std::vector<std::any> &args) const {
    return constructor_(args);
}

const std::vector<std::string> &ConstructorInfo::getParamTypes() const {
    return paramTypes_;
}
