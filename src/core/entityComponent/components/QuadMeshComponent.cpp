//
// Created by Magnitola on 20.09.2025.
//

#include "QuadMeshComponent.h"

#include <iostream>
#include <render/Model.h>

#include "assetManager/AssetManager.h"

QuadMeshComponent::QuadMeshComponent() {
    bCanBeUpdated = true;

    if (const auto expected = GET_OR_LOAD_ASSET(Model, "assets/models/monkey.obj"); expected.has_value())
        model = expected.value();
    else
        std::cout << "Failed to load model" << std::endl;

    if (const auto expected = GET_OR_LOAD_ASSET(Shader, "shader|assets/shaders/"); expected.has_value())
        model->shader = expected.value();
    else
        std::cout << "Failed to load shader" << std::endl;
}
