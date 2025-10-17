//
// Created by Magnitola on 14.10.2025.
//

#include "FieldInfo.h"

#include <utility>

FieldInfo::FieldInfo(const std::function<const void*(const void *)> &getter,
                     const std::function<void(void *, std::any)> &setter,
                     std::string name,
                     const std::type_index typeIndex)
    : getter_(getter), setter_(setter), name_(std::move(name)), typeId_(typeIndex) {
}

const void *FieldInfo::getValue(const void *object) const {
    return getter_(object);
}

void FieldInfo::setValue(void *object, const std::any &value) const {
    setter_(object, value);
}

const std::string &FieldInfo::getName() const {
    return name_;
}

const std::type_index &FieldInfo::getTypeIndex() const {
    return typeId_;
}
