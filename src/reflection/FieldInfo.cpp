//
// Created by Magnitola on 14.10.2025.
//

#include "FieldInfo.h"

FieldInfo::FieldInfo(const std::function<std::any(void *)> &getter,
                     const std::function<void(void *, std::any)> &setter,
                     const std::string &name,
                     const std::string &type) : getter_(getter), setter_(setter), name_(name), typeName_(type) {
}

std::any FieldInfo::getValue(void *object) const {
    return getter_(object);
}

void FieldInfo::setValue(void *object, const std::any &value) const {
    setter_(object, value);
}

const std::string &FieldInfo::getName() const {
    return name_;
}

const std::string &FieldInfo::getType() const {
    return typeName_;
}
