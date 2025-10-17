//
// Created by Magnitola on 14.10.2025.

#pragma once
#include <any>
#include <functional>
#include <string>
#include <typeindex>


/**
 * Meta-information about a field for reflection system.
 *
 * @note This class is populated by the Reflector and should not be constructed manually.
 */
class FieldInfo {
public:
    FieldInfo(const std::function<const void*(const void *)> &getter,
              const std::function<void(void *, std::any)> &setter,
              std::string name,
              std::type_index typeIndex);

    /**
     * Get field value from object declared this field
     * @param object Ptr to object, declared this field
     * @return Const raw ptr field value
     */
    const void *getValue(const void *object) const;

    /**
     * Set field value in object declared this field
     * @param object Ptr to object, declared this field
     * @param value New field value
     */
    void setValue(void *object, const std::any &value) const;

    /**
     * @return name of the field declared by the owner
     */
    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] const std::type_index &getTypeIndex() const;

private:
    std::function<const void*(const void *)> getter_;
    std::function<void(void *, std::any)> setter_;
    std::string name_;
    std::type_index typeId_;
};
