//
// Created by Magnitola on 20.09.2025.
//

#include "CameraEntity.h"

#include "World.h"
#include "components/CameraComponent.h"
#include "render/Render.h"

CameraEntity::CameraEntity() {
    camera = createComponent<CameraComponent>();
}

void CameraEntity::onSpawned() {
    Entity::onSpawned();

    world->getRender()->setRenderingCamera(*camera);
}
