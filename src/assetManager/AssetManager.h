//
// Created by Magnitola on 07.10.2025.
//

#pragma once
#include <expected>
#include <format>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "Asset.h"
#include "AssetLoader.h"


class AssetLoader;
class Asset;

enum class AssetManagerError {
    LoaderNotFound,
    LoadFailed,
    InvalidAsset,
    AssetNotFound,
};

class AssetManager {
public:
    template<std::derived_from<Asset> T>
    using AssetPtr = std::shared_ptr<T>;

    AssetManager(const AssetManager &) = delete;

    AssetManager &operator=(const AssetManager &) = delete;

    AssetManager(AssetManager &&) = delete;

    AssetManager &operator=(AssetManager &&) = delete;

    static AssetManager &getInstance();

    template<class T> requires std::derived_from<T, Asset>
    void registerAssetLoader(std::unique_ptr<AssetLoader> loader) {
        const size_t hash = typeid(T).hash_code();
        loaders_[hash] = std::move(loader);
    }

    template<class T> requires std::derived_from<T, Asset>
    std::expected<AssetPtr<T>, AssetManagerError> getAsset(const std::string_view path) {
        if (const auto it = assets_.find(std::string(path)); it != assets_.end()) {
            if (auto asset = std::dynamic_pointer_cast<T>(it->second)) {
                return asset;
            }
            return std::unexpected(AssetManagerError::InvalidAsset);
        }
        return std::unexpected(AssetManagerError::AssetNotFound);
    }

    template<class T> requires std::derived_from<T, Asset>
    std::expected<AssetPtr<T>, AssetManagerError> getOrLoadAsset(const std::string_view path) {
        if (auto result = getAsset<T>(path); result.has_value())
            return result.value();
        else if (result.error() != AssetManagerError::AssetNotFound)
            return std::unexpected(result.error());

        const size_t loaderHash = typeid(T).hash_code();
        if (const auto it = loaders_.find(loaderHash); it != loaders_.end()) {
            auto asset = it->second->load(path);
            if (!asset)
                return std::unexpected(AssetManagerError::LoadFailed);

            asset->path_ = path;

            if (!asset->load_impl())
                return std::unexpected(AssetManagerError::LoadFailed);

            asset->loaded_ = true;

            T *typed_asset = dynamic_cast<T *>(asset.release());
            if (!typed_asset)
                return std::unexpected(AssetManagerError::InvalidAsset);
            AssetPtr<T> sharedAsset(typed_asset);

            assets_.emplace(std::string(path), sharedAsset);
            return sharedAsset;
        }
        return std::unexpected(AssetManagerError::LoaderNotFound);
    }

private:
    AssetManager() = default;

    ~AssetManager() = default;

    std::unordered_map<std::string, std::shared_ptr<Asset> > assets_;
    std::unordered_map<size_t, std::unique_ptr<AssetLoader> > loaders_;
};

#define ASSET_MANAGER AssetManager::getInstance()
#define GET_ASSET(type, path) ASSET_MANAGER.getAsset<type>(path)
#define GET_OR_LOAD_ASSET(type, path) ASSET_MANAGER.getOrLoadAsset<type>(path)
