//
// Created by Magnitola on 18.09.2025.
//

#include "Render.h"

#include <iostream>
#include <GL/glew.h>

#include "components/CameraComponent.h"
#include "math/Matrix4x4.h"
#include "math/Transform.h"
#include "render/Model.h"

RenderRequest::RenderRequest(Model &model, Transform &transform) {
    this->model = &model;
    this->transform = &transform;
}

Render::Render() = default;

Render::~Render() = default;

void Render::submitRequest(const RenderRequest request) {
    requests_.push_back(request);
}

void Render::rendering() {
    if (renderCamera_ == nullptr) return;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Matrix4x4 v = renderCamera_->transform->getTransformMatrix();
    const Matrix4x4 p = renderCamera_->GetProjectionMatrix();
    const Matrix4x4 vp = v * p;

    glUniformMatrix4fv(1, 1, GL_FALSE, vp.getData());

    for (const RenderRequest request: requests_) {
        glBindVertexArray(request.model->vao);
        Matrix4x4 transform = request.transform->getTransformMatrix();
        glUniformMatrix4fv(0, 1, GL_FALSE, transform.getData());
        glDrawElements(GL_TRIANGLES, request.model->elementsCount, GL_UNSIGNED_INT, nullptr);
    }

    glBindVertexArray(0);
    requests_.clear();
}

void Render::setRenderingCamera(CameraComponent &camera) {
    renderCamera_ = &camera;
}
