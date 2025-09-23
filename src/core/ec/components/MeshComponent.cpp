//
// Created by Magnitola on 19.09.2025.
//

#include "MeshComponent.h"

#include "Entity.h"
#include "World.h"
#include "math/Transform.h"
#include "render/Render.h"

MeshComponent::MeshComponent() : model(nullptr) {
    bCanBeUpdated = true;
    transform = nullptr;
}

void MeshComponent::update(float deltaTime) {
    super::update(deltaTime);

    const RenderRequest request{*model, *owner->transform};
    owner->world->getRender()->submitRequest(request);

}
