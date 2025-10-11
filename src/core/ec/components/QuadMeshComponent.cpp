//
// Created by Magnitola on 20.09.2025.
//

#include "QuadMeshComponent.h"

#include <iostream>
#include <render/Model.h>

#include "fs/AssetManager.h"

QuadMeshComponent::QuadMeshComponent() {
    bCanBeUpdated = true;

    model = new Model();

    Vector3 verticies[] = {
        {-0.5f, -0.5f, 0.5f},
        {0.5f, -0.5f, 0.5f},
        {0.5f, 0.5f, 0.5f},
        {-0.5f, 0.5f, 0.5f},
        {-0.5f, -0.5f, -0.5f},
        {0.5f, -0.5f, -0.5f},
        {0.5f, 0.5f, -0.5f},
        {-0.5f, 0.5f, -0.5f},
    };

    std::vector<Vertex> data;

    for (Vector3 vector3: verticies) {
        data.push_back(Vertex{vector3, Vector3(), Vector3()});
    }

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        3, 2, 6,
        6, 7, 3,

        0, 1, 5,
        5, 4, 0,

        1, 5, 6,
        6, 2, 1,

        0, 4, 7,
        7, 3, 0
    };

    auto expected = GET_OR_LOAD_ASSET(Shader, "shader|assets/shaders/");
    if (expected.has_value())
        model->shader = expected.value();
    else
        std::cout << "Failed to load shader" << std::endl;
    model->load(data, indices, "genericQuadMesh");
}
