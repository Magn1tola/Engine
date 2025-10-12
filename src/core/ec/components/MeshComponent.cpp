//
// Created by Magnitola on 19.09.2025.
//

#include "MeshComponent.h"

#include "render/Render.h"

MeshComponent::MeshComponent() {
    bCanBeUpdated = true;
}

void MeshComponent::update(float deltaTime) {
    WorldComponent::update(deltaTime);

    Render::getInstance().submitRequest({model, transform});

}
