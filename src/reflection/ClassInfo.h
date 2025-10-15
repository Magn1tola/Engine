//
// Created by Magnitola on 14.10.2025.
//

#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "ConstructorInfo.h"
#include "FieldInfo.h"
#include "MethodInfo.h"


class ClassInfo {
public:
    using FieldMap = std::unordered_map<std::string, FieldInfo>;
    using BaseClasses = std::vector<const ClassInfo *>;
    using MethodMap = std::unordered_map<std::string, MethodInfo>;
    using Constructors = std::vector<ConstructorInfo>;

    explicit ClassInfo(const std::string &className) : className_(className) {
    }

    const std::string &getClassName() const { return className_; }
    const FieldMap &getFields() const { return fields_; }
    const BaseClasses &getBaseClasses() const { return baseClasses_; }
    const MethodMap &getMethods() const { return methodMap_; }
    const Constructors &getConstructors() const { return constructors_; }

    FieldMap getAllFields() const;

    BaseClasses getAllBaseClasses() const;

    MethodMap getAllMethods() const;

    void *construct();
    void *construct(const std::vector<std::any> &args);

    const FieldInfo &getField(const std::string &fieldName) const;
    const MethodInfo &getMethod(const std::string &methodName) const;

private:
    void collectFieldsRecursive(FieldMap &allFields) const;

    void collectBaseClassesRecursive(BaseClasses &allBaseClasses) const;

    void collectMethodsRecursive(MethodMap &allMethods) const;

    void addField(const FieldInfo &field);

    void addBaseClass(const ClassInfo *baseClass);

    void addMethod(const MethodInfo &method);

    void addConstructor(const ConstructorInfo &constructor);

    ConstructorInfo *findConstructor(const std::vector<std::any> &args);

    std::string className_;
    FieldMap fields_;
    BaseClasses baseClasses_;
    MethodMap methodMap_;
    Constructors constructors_;

    friend class Reflector;
};
