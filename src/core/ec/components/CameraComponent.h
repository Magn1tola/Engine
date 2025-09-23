//
// Created by Magnitola on 20.09.2025.
//

#pragma once
#include "WorldComponent.h"

class Matrix4x4;

enum EProjectionType {
    PT_PERSPECTIVE,
    PT_ORTHOGRAPHIC,
};

class CameraComponent : public WorldComponent {
public:
    CameraComponent();

    EProjectionType projectionType = PT_PERSPECTIVE;

    float fov = 90;
    float nearPlane = 0.01f;
    float farPlane = 1000.0f;
    float aspectRatio = 16.0f / 9.0f;

    [[nodiscard]] Matrix4x4 GetViewProjectionMatrix() const;

protected:
    ~CameraComponent() = default;
};
