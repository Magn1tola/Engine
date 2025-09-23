//
// Created by Magnitola on 20.09.2025.
//

#include "QuadMeshEntity.h"

#include "components/QuadMeshComponent.h"
#include "math/Transform.h"
#include "math/Vector3.h"

QuadMeshEntity::QuadMeshEntity() {
    bCanBeUpdated = true;
    quadMesh = createComponent<QuadMeshComponent>();
}

void QuadMeshEntity::update(float deltaTime) {
    Entity::update(deltaTime);

    transform->rotate(Vector3(-50, 30, -70) * deltaTime);
}
