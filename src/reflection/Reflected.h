//
// Created by Magnitola on 14.10.2025.
//

#pragma once
#include <any>
#include <functional>
#include <string>
#include <unordered_map>

#include "FieldInfo.h"
#include "ClassInfo.h"


class ClassInfo;

class Reflectable {
};

template<typename T>
class Reflected : public Reflectable {
    using FieldMap = std::unordered_map<std::string, FieldInfo>;

public:
    static ClassInfo &getClassInfo() {
        static ClassInfo staticClass(typeid(T).name());
        return staticClass;
    }

protected:
    template<typename FieldType>
    static void registerField(const std::string &name, FieldType T::*field_ptr) {
        auto &staticClass = getClassInfo();
        staticClass.addField(FieldInfo(
            [field_ptr](void *obj) -> std::any {
                return static_cast<T *>(obj)->*field_ptr;
            },
            [field_ptr](void *obj, std::any value) {
                static_cast<T *>(obj)->*field_ptr = std::any_cast<FieldType>(value);
            },
            name,
            typeid(FieldType).name()
        ));
    }

    template<typename BaseClass>
        requires std::is_base_of_v<Reflectable, BaseClass>
    static void registerBaseClass() {
        getClassInfo().addBaseClass(&BaseClass::getClassInfo());
    }
};

#define DECLARE_REFLECTED(className) \
    public:\
        using Reflected<className>::getClassInfo;\
    private: \
        using Self = className

#define REFLECTED_BASE(baseClass) \
    static inline const bool _registered_base_##baseClass = []() { \
        Reflected<Self>::registerBaseClass<baseClass>();\
        return true; \
    }()

#define AUTO_REGISTER_FIELD(fieldType, fieldName)\
    static inline const bool _serializable_field_##fieldName = []() { \
        Reflected<Self>::registerField(#fieldName, &Self::fieldName);\
        return true;\
    }()

#define FIELD(fieldType, fieldName)\
    fieldType fieldName;\
    AUTO_REGISTER_FIELD(fieldType, fieldName)

#define FIELD_INIT(fieldType, fieldName, defaultValue)\
    fieldType fieldName = defaultValue;\
    AUTO_REGISTER_FIELD(fieldType, fieldName)
