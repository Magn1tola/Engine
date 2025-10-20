//
// Created by Magnitola on 14.10.2025.
//

#include "FieldInfo.h"

#include <utility>

FieldInfo::FieldInfo(const std::function<void*(void *)> &getter,
                     const std::function<void(void *, std::any)> &setter,
                     std::string name,
                     const std::type_index typeIndex)
    : getter_(getter), setter_(setter), name_(std::move(name)), typeId_(typeIndex) {
}

FieldInfo::FieldInfo(const std::function<void *(void *)> &getter, const std::function<void(void *, std::any)> &setter,
                     std::string name, std::type_index typeIndex, std::type_index elementTypeIndex,
                     std::function<size_t(void *)> getVectorSize, std::function<void(void *, size_t)> setVectorSize,
                     std::function<void *(void *, size_t)> getVectorElement)
    : getter_(getter), setter_(setter), name_(std::move(name)), typeId_(typeIndex),
      elementTypeIndex_(elementTypeIndex), getVectorSize_(std::move(getVectorSize)),
      setVectorSize_(std::move(setVectorSize)), getVectorElement_(std::move(getVectorElement)), isVector_(true) {
}

void *FieldInfo::getValue(void *object) const {
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
