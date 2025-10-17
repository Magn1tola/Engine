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

    float nearPlane = 0.001f;
    float farPlane = 100000.0f;
    float aspectRatio = 16.0f / 9.0f;

    /**
     * For orthographic projection only
     */
    float size = 20.0f;

    /**
     * For perspective projection only
     */
    float fov = 60.0f;

    [[nodiscard]] Matrix4x4 GetProjectionMatrix() const;

    BEGIN_REFLECTED_TYPE(CameraComponent)
        BASE_TYPE(WorldComponent)
        CONSTRUCTOR()
        FIELDS(projectionType, nearPlane, farPlane, aspectRatio, size, fov)
    END_REFLECTED_TYPE();
};
