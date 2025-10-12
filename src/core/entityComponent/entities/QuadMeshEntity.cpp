//
// Created by Magnitola on 20.09.2025.
//

#include "QuadMeshEntity.h"

#include "math/Transform.h"

QuadMeshEntity::QuadMeshEntity() {
    bCanBeUpdated = true;
    quadMesh = CREATE_UNIQUE_COMPONENT(QuadMeshComponent);
}

void QuadMeshEntity::update(float deltaTime) {
    Entity::update(deltaTime);

    transform->rotate(Vector3(-50, 30, -70) * deltaTime);
}
