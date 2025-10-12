//
// Created by Magnitola on 07.10.2025.
//

#include "AssetManager.h"

AssetManager &AssetManager::getInstance() {
    static AssetManager instance;
    return instance;
}
