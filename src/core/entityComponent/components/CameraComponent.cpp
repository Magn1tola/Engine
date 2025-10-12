//
// Created by Magnitola on 20.09.2025.
//

#include "CameraComponent.h"

#include "math/Matrix4x4.h"

CameraComponent::CameraComponent() {
    bCanBeUpdated = true;
}

Matrix4x4 CameraComponent::GetProjectionMatrix() const {
    switch (projectionType) {
        case PT_PERSPECTIVE:
            return Matrix4x4::perspective(fov, aspectRatio, nearPlane, farPlane);
        case PT_ORTHOGRAPHIC:
            const float halfHeight = size / 2;
            const float halfWidth = halfHeight * aspectRatio;
            return Matrix4x4::orthographic(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane);
    }
    return {};
}
