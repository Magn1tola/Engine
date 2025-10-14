//
// Created by Magnitola on 14.10.2025.
//

#pragma once
#include <any>
#include <functional>
#include <string>


class FieldInfo {
public:
    FieldInfo(const std::function<std::any(void *)> &getter,
              const std::function<void(void *, std::any)> &setter,
              const std::string &name,
              const std::string &type);

    std::any getValue(void *object) const;

    void setValue(void *object, const std::any &value) const;

    const std::string &getName() const;

    const std::string &getType() const;

private:
    std::function<std::any(void *)> getter_;
    std::function<void(void *, std::any)> setter_;
    std::string name_;
    std::string typeName_;
};
