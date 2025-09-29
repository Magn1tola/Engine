//
// Created by Magnitola on 21.09.2025.
//

#pragma once
#include "EntityComponent.h"


class Transform;

class WorldComponent : public EntityComponent {
public:
    WorldComponent();

    Transform* transform;

    void setOwner(Entity &newOwner) override;
protected:
    ~WorldComponent() = default;
};
