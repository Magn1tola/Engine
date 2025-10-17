//
// Created by Magnitola on 14.10.2025.
//

#pragma once
#include <any>
#include <functional>
#include <string>

#include "TypeInfo.h"
#include "utils/ForEachMacros.h"

/**
 * Central reflection registry for types.
 *
 * Provides runtime type information (RTTI) through automatic registration of types, fields, methods, and inheritance hierarchies.
 *
 * @note This is a singleton-like static class that maintains global type registry.
 * @warning Not thread-safe during registration phase. Type registration should typically happen during static initialization.
 */
class Reflector {
public:
    /**
     * Registers a type with the reflection system.
     * @tparam T Type to register
     * @note This must be called before registering any fields/methods for the type
     */
    template<typename T>
    static void registerType() {
        auto name = typeid(T).name();
        types_.emplace(name, TypeInfo(name));
    }

    /**
     * Retrieves type information by compile-time type.
     * @tparam T Type to query
     * @return Pointer to TypeInfo or nullptr if type not registered
     */
    template<typename T>
    static TypeInfo *getTypeInfo() {
        if (types_.contains(typeid(T).name()))
            return &types_.at(typeid(T).name());
        return nullptr;
    }

    /**
     * Retrieves type information by type name.
     * @param name Type name (as returned by typeid(T).name())
     * @return Pointer to TypeInfo or nullptr if type not registered
     * @warning Uses compiler-mangled names. For demangled names, additional processing would be required.
     */
    static TypeInfo *getTypeInfo(const std::string &name) {
        if (types_.contains(name))
            return &types_.at(name);
        return nullptr;
    }

    /**
     * Registers a field for reflection.
     * @tparam T Class type containing the field
     * @tparam FieldType Type of the field
     * @param name Field name for reflection
     * @param field_ptr Pointer-to-member for the field
     */
    template<typename T, typename FieldType>
    static void registerField(const std::string &name, FieldType T::*field_ptr) {
        auto classInfo = getTypeInfo<T>();
        FieldInfo info(
            [field_ptr](const void *obj) -> const void * {
                return &(static_cast<const T *>(obj)->*field_ptr);
            },
            [field_ptr](void *obj, std::any value) {
                static_cast<T *>(obj)->*field_ptr = std::any_cast<FieldType>(value);
            },
            name,
            typeid(FieldType)
        );
        classInfo->addField(info);
    }

    /**
     * Establishes inheritance relationship in reflection system.
     * @tparam T Derived class
     * @tparam BaseClass Base class
     * @note This enables getAllFields() and getAllMethods() to work correctly across inheritance hierarchies.
     */
    template<typename T, typename BaseClass>
    static void registerBaseClass() {
        getTypeInfo<T>()->addBaseClass(BaseClass::getTypeInfo());
    }

    /**
     * Registers a non-const member method for reflection.
     * @tparam T Class type
     * @tparam Ret Return type
     * @tparam Args Method argument types
     * @param name Method name for reflection
     * @param method Pointer-to-member method
     */
    template<typename T, typename Ret, typename... Args>
    static void registerMethod(const std::string &name, Ret (T::*method)(Args...)) {
        auto classInfo = getTypeInfo<T>();

        std::vector<std::string> paramTypes = {typeid(Args).name()...};

        auto invoker = [method](void *obj, std::vector<std::any> args) -> std::any {
            if constexpr (std::is_void_v<Ret>) {
                invokeMethodImpl(static_cast<T *>(obj), method, args, std::index_sequence_for<Args...>{});
                return {};
            } else {
                return invokeMethodImpl(static_cast<T *>(obj), method, args, std::index_sequence_for<Args...>{});
            }
        };

        classInfo->addMethod(MethodInfo(name, typeid(Ret).name(), paramTypes, invoker));
    }

    /**
     * Registers a const member method for reflection.
     * @tparam T Class type
     * @tparam Ret Return type
     * @tparam Args Method argument types
     * @param name Method name for reflection
     * @param method Pointer-to-member const method
     */
    template<typename T, typename Ret, typename... Args>
    static void registerMethod(const std::string &name, Ret (T::*method)(Args...) const) {
        auto classInfo = getTypeInfo<T>();

        std::vector<std::type_index> paramTypes = {typeid(Args)...};

        auto invoker = [method](void *obj, std::vector<std::any> args) -> std::any {
            if constexpr (std::is_void_v<Ret>) {
                invokeMethodImpl(static_cast<T *>(obj), method, args, std::index_sequence_for<Args...>{});
                return {};
            } else {
                return invokeMethodImpl(static_cast<T *>(obj), method, args, std::index_sequence_for<Args...>{});
            }
        };

        classInfo->addMethod(MethodInfo(name, typeid(Ret).name(), paramTypes, invoker));
    }

    /**
     * Registers a constructor with specified arguments.
     * @tparam T Class type to construct
     * @tparam Args Constructor argument types
     * @note Each constructor must be registered separately
     */
    template<typename T, typename... Args>
    static void registerConstructor() {
        auto classInfo = getTypeInfo<T>();

        std::vector<std::string> paramTypes = {typeid(Args).name()...};

        auto constructor = [](std::vector<std::any> args) -> void * {
            return constructImpl<T, Args...>(args, std::index_sequence_for<Args...>{});
        };

        classInfo->addConstructor(ConstructorInfo(paramTypes, constructor));
    }

private:
    static inline std::unordered_map<std::string, TypeInfo> types_;

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

// ===================================================================
// Reflection Macros for declarative type registration
// ===================================================================

/**
 * Begins type registration block. Must be placed in class declaration.
 * @param className Name of the class being reflected
 */
#define BEGIN_REFLECTED_TYPE(className)\
    public:\
        static TypeInfo *getTypeInfo() { return Reflector::getTypeInfo<className>(); }\
    private: \
        static inline const bool _registeredReflected##className = []() {\
            using ReflectedClass = className;\
            Reflector::registerType<className>();

/**
 * Registers a base class for the current reflected type
 * @param baseClass Base class name
 */
#define BASE_TYPE(baseClass)\
    Reflector::registerBaseClass<ReflectedClass, baseClass>();

/**
 * Registers default (parameterless) constructor
 */
#define CONSTRUCTOR()\
    Reflector::registerConstructor<ReflectedClass>();

/**
 * Registers constructor with specific arguments
 * @param ... Constructor argument types
 */
#define CONSTRUCTOR_ARGS(...)\
    Reflector::registerConstructor<ReflectedClass, __VA_ARGS__>();

/**
 * Registers a single field for reflection
 * @param fieldName Field name (without quotes)
 */
#define FIELD(fieldName)\
    Reflector::registerField<ReflectedClass>(#fieldName, &ReflectedClass::fieldName);

/**
 * Registers multiple fields at once
 * @param ... Comma-separated field names
 */
#define FIELDS(...)\
    FOR_EACH(FIELD, __VA_ARGS__)

/**
 * Registers a single method for reflection
 * @param methodName Method name (without quotes)
 */
#define METHOD(methodName)\
    Reflector::registerMethod<ReflectedClass>(#methodName, &ReflectedClass::methodName);

/**
 * Registers multiple methods at once
 * @param ... Comma-separated method names
 */
#define METHODS(...)\
    FOR_EACH(METHOD, __VA_ARGS__)

/**
 * Ends type registration block
 */
#define END_REFLECTED_TYPE()\
    return true;\
    }()
