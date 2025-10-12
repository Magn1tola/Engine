//
// Created by Magnitola on 20.09.2025.
//

#include "CameraEntity.h"

#include "components/CameraComponent.h"
#include "render/Render.h"

CameraEntity::CameraEntity() {
    camera = CREATE_SHARED_COMPONENT(CameraComponent);
}

void CameraEntity::onSpawned() {
    Entity::onSpawned();

    Render::getInstance().setRenderingCamera(camera);
}
