//
// Created by Magnitola on 20.09.2025.
//

#pragma once
#include "Entity.h"


class CameraComponent;

class CameraEntity : public Entity {
public:
    CameraEntity();

    CameraComponent *camera;

    void onSpawned() override;
};
