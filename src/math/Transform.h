//
// Created by Magnitola on 18.09.2025.
//

#pragma once

#include <memory>

#include "Matrix4x4.h"
#include "Quaternion.h"
#include "Vector3.h"

class Transform {
public:
    Transform();

    ~Transform();

    [[nodiscard]] const Vector3 *getPosition() const {
        return &position_;
    }

    [[nodiscard]] const Quaternion *getRotation() const {
        return &rotation_;
    }

    [[nodiscard]] const Vector3 *getScale() const {
        return &scale_;
    }

    Vector3 getWorldPosition();

    Quaternion getWorldRotation();

    Vector3 getWorldScale();

    void attachTo(const std::shared_ptr<Transform> &newParent);

    void setPosition(const Vector3 &newPosition);

    void setRotation(const Quaternion &newRotation);

    void setRotation(const Vector3 &eulerAngles);

    void setScale(const Vector3 &newScale);

    void translate(const Vector3 &translation);

    void rotate(const Quaternion &angles);

    void rotate(const Vector3 &eulerAngles);

    void scaleBy(const Vector3 &scaling);

    [[nodiscard]] Matrix4x4 getTransformMatrix();

private:
    Vector3 position_;
    Quaternion rotation_;
    Vector3 scale_;

    Matrix4x4 worldMatrix_;

    std::weak_ptr<Transform> parent_;

    bool isDirty = false;

    void updateWorldMatrix();

    void tryUpdateWorldMatrix();
};
