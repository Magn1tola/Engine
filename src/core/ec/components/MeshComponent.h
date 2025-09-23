//
// Created by Magnitola on 19.09.2025.
//

#pragma once
#include "WorldComponent.h"


class Transform;
class Model;

class MeshComponent : public WorldComponent {
public:
    MeshComponent();

    Model *model;
    Transform *transform;

protected:
    ~MeshComponent() = default;

    void update(float deltaTime) override;

private:
    typedef EntityComponent super;
};
