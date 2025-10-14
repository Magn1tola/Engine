//
// Created by Magnitola on 14.10.2025.
//

#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "FieldInfo.h"


class ClassInfo {
    using FieldMap = std::unordered_map<std::string, FieldInfo>;
    using BaseClasses = std::vector<const ClassInfo *>;

public:
    explicit ClassInfo(const std::string &className) : className_(className) {
    }

    void addField(const FieldInfo &field);

    void addBaseClass(const ClassInfo *baseClass);

    const std::string &getClassName() const { return className_; }
    const FieldMap &getFields() const { return fields_; }
    const BaseClasses &getBaseClasses() const { return baseClasses_; }

    FieldMap getAllFields() const;

    BaseClasses getAllBaseClasses() const;

private:
    void collectFieldsRecursive(FieldMap &allFields) const;
    void collectBaseClassesRecursive(BaseClasses &allBaseClasses) const;

    std::string className_;
    FieldMap fields_;
    BaseClasses baseClasses_;
};
