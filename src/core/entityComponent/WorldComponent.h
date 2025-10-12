//
// Created by Magnitola on 21.09.2025.
//

#pragma once
#include <memory>

#include "EntityComponent.h"


class Transform;

class WorldComponent : public EntityComponent {
public:
    WorldComponent();

    ~WorldComponent() override = default;

    std::shared_ptr<Transform> transform;

    void setOwner(Entity *newOwner) override;
};
