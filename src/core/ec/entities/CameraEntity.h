//
// Created by Magnitola on 20.09.2025.
//

#pragma once
#include <memory>

#include "Entity.h"


class CameraComponent;

class CameraEntity : public Entity {
public:
    CameraEntity();

    ~CameraEntity() override = default;

    std::shared_ptr<CameraComponent> camera;

    void onSpawned() override;
};
