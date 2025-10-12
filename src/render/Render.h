//
// Created by Magnitola on 18.09.2025.
//

#pragma once
#include <memory>
#include <vector>


class CameraComponent;
class Model;
class Transform;

struct RenderRequest {
    const std::shared_ptr<Model> &model;
    const std::shared_ptr<Transform> &transform;

    RenderRequest(const std::shared_ptr<Model> &model, const std::shared_ptr<Transform> &transform) : model(model), transform(transform) {};
};

class Render {
public:
    Render(const Render &) = delete;

    Render &operator=(const Render &) = delete;

    Render(Render &&) = delete;

    Render &operator=(Render &&) = delete;

    static Render &getInstance();

    void submitRequest(RenderRequest request);

    void rendering();

    void setRenderingCamera(const std::shared_ptr<CameraComponent> &camera);

private:
    Render() = default;

    ~Render() = default;

    std::shared_ptr<CameraComponent> renderCamera_;
    std::vector<RenderRequest> requests_;
};
