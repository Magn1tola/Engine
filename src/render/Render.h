//
// Created by Magnitola on 18.09.2025.
//

#pragma once
#include <vector>


class CameraComponent;
class Model;
class Transform;

struct RenderRequest {
    Model *model;
    Transform *transform;

    RenderRequest(Model &model, Transform &transform);
};

class Render {
public:
    Render();

    ~Render();

    void submitRequest(RenderRequest request);

    void rendering();

    void setRenderingCamera(CameraComponent &camera);

private:
    CameraComponent *renderCamera_;
    std::vector<RenderRequest> requests_;
};
