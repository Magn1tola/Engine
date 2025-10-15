//
// Created by Magnitola on 14.10.2025.
//

#pragma once
#include <any>
#include <functional>
#include <string>

#include "ClassInfo.h"


class Reflector {
public:
    template<typename T>
    static ClassInfo &getClassInfo() {
        static ClassInfo staticClass(typeid(T).name());
        return staticClass;
    }

    template<typename T, typename FieldType>
    static void registerField(const std::string &name, FieldType T::*field_ptr) {
        auto &classInfo = getClassInfo<T>();
        FieldInfo info(
            [field_ptr](void *obj) -> std::any {
                return static_cast<T *>(obj)->*field_ptr;
            },
            [field_ptr](void *obj, std::any value) {
                static_cast<T *>(obj)->*field_ptr = std::any_cast<FieldType>(value);
            },
            name,
            typeid(FieldType).name()
        );
        classInfo.addField(info);
    }

    template<typename T, typename BaseClass>
    static void registerBaseClass() {
        getClassInfo<T>().addBaseClass(&BaseClass::getClassInfo());
    }

    template<typename T, typename Ret, typename... Args>
    static void registerMethod(const std::string &name, Ret (T::*method)(Args...)) {
        auto &classInfo = getClassInfo<T>();

        std::vector<std::string> paramTypes = {typeid(Args).name()...};

        auto invoker = [method](void *obj, std::vector<std::any> args) -> std::any {
            if constexpr (std::is_void_v<Ret>) {
                invokeMethodImpl(static_cast<T *>(obj), method, args, std::index_sequence_for<Args...>{});
                return std::any();
            } else {
                return invokeMethodImpl(static_cast<T *>(obj), method, args, std::index_sequence_for<Args...>{});
            }
        };

        classInfo.addMethod(MethodInfo(name, typeid(Ret).name(), paramTypes, invoker));
    }

    template<typename T, typename Ret, typename... Args>
    static void registerMethod(const std::string &name, Ret (T::*method)(Args...) const) {
        auto &classInfo = getClassInfo<T>();

        std::vector<std::string> paramTypes = {typeid(Args).name()...};

        auto invoker = [method](void *obj, std::vector<std::any> args) -> std::any {
            if constexpr (std::is_void_v<Ret>) {
                invokeMethodImpl(static_cast<T *>(obj), method, args, std::index_sequence_for<Args...>{});
                return std::any();
            } else {
                return invokeMethodImpl(static_cast<T *>(obj), method, args, std::index_sequence_for<Args...>{});
            }
        };

        classInfo.addMethod(MethodInfo(name, typeid(Ret).name(), paramTypes, invoker));
    }

    template<typename T, typename... Args>
    static void registerConstructor() {
        auto &classInfo = getClassInfo<T>();

        std::vector<std::string> paramTypes = {typeid(Args).name()...};

        auto constructor = [](std::vector<std::any> args) -> void * {
            return constructImpl<T, Args...>(args, std::index_sequence_for<Args...>{});
        };

        classInfo.addConstructor(ConstructorInfo(paramTypes, constructor));
    }

private:
    template<typename T, typename Ret, typename... Args, size_t... I>
    static auto invokeMethodImpl(T *obj, Ret (T::*method)(Args...), const std::vector<std::any> &args,
                                 std::index_sequence<I...>) {
        return (obj->*method)(std::any_cast<Args>(args[I])...);
    }

    template<typename T, typename Ret, typename... Args, size_t... I>
    static auto invokeMethodImpl(T *obj, Ret (T::*method)(Args...) const, const std::vector<std::any> &args,
                                 std::index_sequence<I...>) {
        return (obj->*method)(std::any_cast<Args>(args[I])...);
    }

    template<typename T, typename... Args, size_t... I>
    static void *constructImpl(const std::vector<std::any> &args, std::index_sequence<I...>) {
        return new T(std::any_cast<Args>(args[I])...);
    }
};

#define DECLARE_REFLECTED(className) \
    public:\
        static ClassInfo &getClassInfo() { return Reflector::getClassInfo<className>(); }\
    private: \
        using ReflectedClass = className;\
        CONSTRUCTOR()

#define REFLECTED_BASE(baseClass) \
    static inline const bool _registered_base_##baseClass = []() { \
        Reflector::registerBaseClass<ReflectedClass, baseClass>();\
        return true; \
    }()

#define FIELD(fieldName)\
    static inline const bool _registered_field_##fieldName = []() { \
        Reflector::registerField<ReflectedClass>(#fieldName, &ReflectedClass::fieldName);\
        return true;\
    }()

#define METHOD(methodName) \
    static inline const bool _registered_method_##methodName = []() { \
        Reflector::registerMethod<ReflectedClass>(#methodName, &ReflectedClass::methodName); \
        return true; \
    }()

#define CONSTRUCTOR() \
    static inline const bool _registered_constructor_ = []() { \
        Reflector::registerConstructor<ReflectedClass>(); \
        return true; \
    }()

#define CONSTRUCTOR_ARGS(...)\
    static inline const bool _registered_constructor_ = []() { \
        Reflector::registerConstructor<ReflectedClass, __VA_ARGS__>(); \
        return true; \
    }()
