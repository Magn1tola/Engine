//
// Created by Magnitola on 11.10.2025.
//

#pragma once
#include <memory>


class Asset;

class AssetLoader {
public:
    virtual ~AssetLoader() = default;

    virtual std::unique_ptr<Asset> load(std::string_view path) = 0;
};
