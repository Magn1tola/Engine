//
// Created by Magnitola on 14.10.2025.
//

#include "ClassInfo.h"

void ClassInfo::addField(const FieldInfo &field) {
    fields_.emplace(field.getName(), field);
}

void ClassInfo::addBaseClass(const ClassInfo *baseClass) {
    baseClasses_.push_back(baseClass);
}

ClassInfo::FieldMap ClassInfo::getAllFields() const {
    FieldMap allFields;
    collectFieldsRecursive(allFields);
    return allFields;
}

ClassInfo::BaseClasses ClassInfo::getAllBaseClasses() const {
    BaseClasses allBaseClasses;
    collectBaseClassesRecursive(allBaseClasses);
    return allBaseClasses;
}

void ClassInfo::collectFieldsRecursive(FieldMap &allFields) const {
    for (const auto &baseClass: baseClasses_) {
        baseClass->collectFieldsRecursive(allFields);
    }
    allFields.insert(fields_.begin(), fields_.end());
}

void ClassInfo::collectBaseClassesRecursive(BaseClasses &allBaseClasses) const {
    for (const auto &baseClass: baseClasses_) {
        baseClass->collectBaseClassesRecursive(allBaseClasses);
    }
    allBaseClasses.insert(allBaseClasses.begin(), baseClasses_.begin(), baseClasses_.end());
}
