//
// Created by Magnitola on 19.09.2025.
//

#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Shader.h"
#include "../math/Vector3.h"

class Transform;

struct Vertex {
    Vector3 position;
    Vector3 normal;
    Vector3 texCoords;
};

class Model {
public:
    Model();

    ~Model();

    std::shared_ptr<Shader> shader;

    std::string name;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int elementsCount;

    void load(const std::vector<Vertex> &data, const std::vector<unsigned int> &indices, const std::string &modelName);

    void unload();

};
