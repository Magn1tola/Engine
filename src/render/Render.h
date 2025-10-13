//
// Created by Magnitola on 18.09.2025.
//

#pragma once
#include <memory>
#include <vector>

#include "utils/Singleton.h"


class CameraComponent;
class Model;
class Transform;

struct RenderRequest {
    const std::shared_ptr<Model> &model;
    const std::shared_ptr<Transform> &transform;

    RenderRequest(const std::shared_ptr<Model> &model, const std::shared_ptr<Transform> &transform)
        : model(model), transform(transform) {
    };
};

class Render : public Singleton<Render> {
public:
    void submitRequest(RenderRequest request);

    void rendering();

    void setRenderingCamera(const std::shared_ptr<CameraComponent> &camera);

private:
    std::shared_ptr<CameraComponent> renderCamera_;
    std::vector<RenderRequest> requests_;
};
