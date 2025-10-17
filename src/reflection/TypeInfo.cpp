//
// Created by Magnitola on 14.10.2025.
//

#include "TypeInfo.h"

void TypeInfo::addField(const FieldInfo &field) {
    fields_.emplace(field.getName(), field);
}

void TypeInfo::addBaseClass(const TypeInfo *baseClass) {
    baseClasses_.emplace_back(baseClass);
}

void TypeInfo::addMethod(const MethodInfo &method) {
    methodMap_.emplace(method.getName(), method);
}

void TypeInfo::addConstructor(const ConstructorInfo &constructor) {
    constructors_.emplace_back(constructor);
}

TypeInfo::FieldMap TypeInfo::getAllFields() const {
    FieldMap allFields;
    collectFieldsRecursive(allFields);
    return allFields;
}

TypeInfo::BaseClasses TypeInfo::getAllBaseClasses() const {
    BaseClasses allBaseClasses;
    collectBaseClassesRecursive(allBaseClasses);
    return allBaseClasses;
}

TypeInfo::MethodMap TypeInfo::getAllMethods() const {
    MethodMap allMethods;
    collectMethodsRecursive(allMethods);
    return allMethods;
}

void *TypeInfo::construct() {
    constexpr std::vector<std::any> args;
    return construct(args);
}

void *TypeInfo::construct(const std::vector<std::any> &args) {
    if (findConstructor(args) != nullptr) {
        return findConstructor(args)->construct(args);
    }
    return nullptr;
}

const FieldInfo *TypeInfo::getField(const std::string &fieldName) const {
    if (fields_.contains(fieldName)) {
        return &fields_.find(fieldName)->second;
    }
    if (const auto fields = getAllFields(); fields.contains(fieldName)) {
        return &fields.find(fieldName)->second;
    }
    return nullptr;
}

const MethodInfo *TypeInfo::getMethod(const std::string &methodName) const {
    if (methodMap_.contains(methodName)) {
        return &methodMap_.find(methodName)->second;
    }
    if (const auto methods = getAllMethods(); methods.contains(methodName)) {
        return &methods.find(methodName)->second;
    }
    return nullptr;
}

void TypeInfo::collectFieldsRecursive(FieldMap &allFields) const {
    for (const auto &baseClass: baseClasses_) {
        baseClass->collectFieldsRecursive(allFields);
    }
    allFields.insert(fields_.begin(), fields_.end());
}

void TypeInfo::collectBaseClassesRecursive(BaseClasses &allBaseClasses) const {
    for (const auto &baseClass: baseClasses_) {
        baseClass->collectBaseClassesRecursive(allBaseClasses);
    }
    allBaseClasses.insert(allBaseClasses.begin(), baseClasses_.begin(), baseClasses_.end());
}

void TypeInfo::collectMethodsRecursive(MethodMap &allMethods) const {
    for (const auto &baseClass: baseClasses_) {
        baseClass->collectMethodsRecursive(allMethods);
    }
    allMethods.insert(methodMap_.begin(), methodMap_.end());
}

ConstructorInfo *TypeInfo::findConstructor(const std::vector<std::any> &args) {
    std::vector<std::string> argsTypes;
    for ([[maybe_unused]] const auto &arg: args) {
        argsTypes.emplace_back(typeid(arg).name());
    }

    for (auto &constructor: constructors_) {
        if (constructor.getParamTypes() == argsTypes)
            return &constructor;
    }
    return nullptr;
}
