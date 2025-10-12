//
// Created by Magnitola on 20.09.2025.
//

#pragma once

#include <unordered_map>

#include "assetManager/Asset.h"


class Vector3;
class Matrix4x4;

class Shader : public Asset {
public:
    Shader() : Asset(), programId_(0) {
    }

    void use() const;

    void set_uniform(const std::string &name, int value);

    void set_uniform(const std::string &name, float value);

    void set_uniform(const std::string &name, const Vector3 &vector);

    void set_uniform(const std::string &name, const Matrix4x4 &matrix);

private:
    bool load_impl() override;

    void unload_impl() override;

    unsigned int programId_;

    std::unordered_map<std::string, int> uniforms_;

    int findUniform(const std::string &name);

    friend class ShaderAssetLoader;
};
