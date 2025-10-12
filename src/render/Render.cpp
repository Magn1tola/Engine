//
// Created by Magnitola on 18.09.2025.
//

#include "Render.h"

#include <iostream>
#include <memory>
#include <GL/glew.h>

#include "Shader.h"
#include "components/CameraComponent.h"
#include "math/Matrix4x4.h"
#include "math/Transform.h"
#include "render/Model.h"
#include "assetManager/AssetManager.h"

Render &Render::getInstance() {
    static Render render;
    return render;
}

void Render::submitRequest(const RenderRequest request) {
    requests_.push_back(request);
}

void Render::rendering() {
    if (renderCamera_ == nullptr) return;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Matrix4x4 v = renderCamera_->transform->getTransformMatrix();
    const Matrix4x4 p = renderCamera_->GetProjectionMatrix();
    const Matrix4x4 vp = v * p;

    for (const RenderRequest request: requests_) {
        request.model->shader->use();
        glBindVertexArray(request.model->vao);
        request.model->shader->set_uniform("vp", vp);
        Matrix4x4 transform = request.transform->getTransformMatrix();
        request.model->shader->set_uniform("model", transform);
        glDrawElements(GL_TRIANGLES, request.model->elementsCount, GL_UNSIGNED_INT, nullptr);
    }

    glBindVertexArray(0);
    requests_.clear();
}

void Render::setRenderingCamera(const std::shared_ptr<CameraComponent> &camera) {
    renderCamera_ = camera;
}
