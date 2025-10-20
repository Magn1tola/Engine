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
    FieldInfo(const std::function<void*(void *)> &getter,
              const std::function<void(void *, std::any)> &setter,
              std::string name,
              std::type_index typeIndex);

    /**
     * Constructor for vector fields with additional vector-specific functions
     */
    FieldInfo(const std::function<void*(void *)> &getter,
              const std::function<void(void *, std::any)> &setter,
              std::string name,
              std::type_index typeIndex,
              std::type_index elementTypeIndex,
              std::function<size_t(void *)> getVectorSize,
              std::function<void(void *, size_t)> setVectorSize,
              std::function<void*(void *, size_t)> getVectorElement);

    /**
     * Get field value from object declared this field
     * @param object Ptr to object, declared this field
     * @return Const raw ptr field value
     */
    void *getValue(void *object) const;

    /**
     * Set field value in object declared this field
     * @param object Ptr to object, declared this field
     * @param value New field value
     */
    void setValue(void *object, const std::any &value) const;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] const std::type_index &getTypeIndex() const;

    [[nodiscard]] bool isVector() const { return isVector_; }
    [[nodiscard]] const std::type_index &getElementTypeIndex() const { return elementTypeIndex_; }
    size_t getVectorSize(void *object) const { return getVectorSize_(object); }
    void setVectorSize(void *object, size_t size) const { setVectorSize_(object, size); }
    void *getVectorElement(void *object, size_t index) const { return getVectorElement_(object, index); }

private:
    std::function<void*(void *)> getter_;
    std::function<void(void *, std::any)> setter_;
    std::string name_;
    std::type_index typeId_;
    bool isVector_ = false;
    std::type_index elementTypeIndex_ = typeid(void);
    std::function<size_t(void *)> getVectorSize_;
    std::function<void(void *, size_t)> setVectorSize_;
    std::function<void*(void *, size_t)> getVectorElement_;
};
