//
// Created by Magnitola on 20.09.2025.
//

#include "CameraComponent.h"

#include "math/Matrix4x4.h"
#include "math/Transform.h"

CameraComponent::CameraComponent() = default;

Matrix4x4 CameraComponent::GetViewProjectionMatrix() const {
    switch (projectionType) {
        case PT_PERSPECTIVE:
            return Matrix4x4::perspective(fov, aspectRatio, nearPlane, farPlane) * transform->getTransformMatrix();
        case PT_ORTHOGRAPHIC:
            return Matrix4x4::orthographic(-1, 1, -1, 1, nearPlane, farPlane) * transform->getTransformMatrix();
    }
    return {};
}
