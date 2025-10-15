//
// Created by Magnitola on 20.09.2025.
//

#pragma once
#include "Entity.h"
#include "components/QuadMeshComponent.h"


class QuadMeshEntity : public Entity {
    DECLARE_REFLECTED(QuadMeshEntity);
    REFLECTED_BASE(Entity);

public:
    QuadMeshEntity();

    ~QuadMeshEntity() override = default;

    std::unique_ptr<QuadMeshComponent> quadMesh;

protected:
    void update(float deltaTime) override;
};
