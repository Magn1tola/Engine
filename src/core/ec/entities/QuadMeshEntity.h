//
// Created by Magnitola on 20.09.2025.
//

#pragma once
#include "../Entity.h"


class MeshComponent;
class QuadMeshComponent;

class QuadMeshEntity : public Entity {
public:
    QuadMeshEntity();

    QuadMeshComponent *quadMesh;

protected:
    ~QuadMeshEntity() = default;

    void update(float deltaTime) override;
};
