//
// Created by Magnitola on 08.10.2025.
//

#pragma once
#include <string>

#include "EngineObject.h"


class Asset : public EngineObject {
public:
    Asset() = default;

    ~Asset() override = default;

    [[nodiscard]] std::string_view getPath() const noexcept { return path_; }
    [[nodiscard]] bool isLoaded() const noexcept { return loaded_; }

protected:
    std::string_view path_;
    bool loaded_ = false;

    virtual bool load_impl() = 0;

    virtual void unload_impl() = 0;

    friend class AssetManager;
};
