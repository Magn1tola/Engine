//
// Created by Magnitola on 19.09.2025.
//

#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Shader.h"
#include "math/Vector2.h"
#include "math/Vector3.h"

class Transform;

struct Vertex {
    Vector3 position;
    Vector3 normal;
    Vector2 texCoords;
};

class Model : public Asset {
public:
    Model();

    ~Model() override;

    std::shared_ptr<Shader> shader;

    std::string name;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int elementsCount;

protected:
    bool load_impl() override;

    void unload_impl() override;

private:
    std::vector<Vertex> vertices_;
    std::vector<unsigned int> indices_;

    friend class ModelAssetLoader;
};
