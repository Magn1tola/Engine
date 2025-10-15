//
// Created by Magnitola on 14.10.2025.
//

#include "ClassInfo.h"

void ClassInfo::addField(const FieldInfo &field) {
    fields_.emplace(field.getName(), field);
}

void ClassInfo::addBaseClass(const ClassInfo *baseClass) {
    baseClasses_.emplace_back(baseClass);
}

void ClassInfo::addMethod(const MethodInfo &method) {
    methodMap_.emplace(method.getName(), method);
}

void ClassInfo::addConstructor(const ConstructorInfo &constructor) {
    constructors_.emplace_back(constructor);
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

ClassInfo::MethodMap ClassInfo::getAllMethods() const {
    MethodMap allMethods;
    collectMethodsRecursive(allMethods);
    return allMethods;
}

void *ClassInfo::construct() {
    constexpr std::vector<std::any> args;
    return findConstructor(args)->construct(args);
}

void *ClassInfo::construct(const std::vector<std::any> &args) {
    return findConstructor(args)->construct(args);
}

const FieldInfo &ClassInfo::getField(const std::string &fieldName) const {
    return fields_.find(fieldName)->second;
}

const MethodInfo &ClassInfo::getMethod(const std::string &methodName) const {
    return methodMap_.find(methodName)->second;
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

void ClassInfo::collectMethodsRecursive(MethodMap &allMethods) const {
    for (const auto &baseClass: baseClasses_) {
        baseClass->collectMethodsRecursive(allMethods);
    }
    allMethods.insert(methodMap_.begin(), methodMap_.end());
}

ConstructorInfo *ClassInfo::findConstructor(const std::vector<std::any> &args) {
    std::vector<std::string> argsTypes;
    for ([[maybe_unused]] auto arg : args) {
        argsTypes.push_back(typeid(arg).name());
    }

    for (int i = 0; i < constructors_.size(); i++) {
        if (constructors_[i].getParamTypes() == argsTypes)
            return &constructors_[i];
    }
    return nullptr;
}
