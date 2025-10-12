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

    ~MeshComponent() override = default;

    std::shared_ptr<Model> model;

protected:
    void update(float deltaTime) override;
};
