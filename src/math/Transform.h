//
// Created by Magnitola on 18.09.2025.
//

#pragma once

#include "Matrix4x4.h"
#include "Quaternion.h"
#include "Vector3.h"

class Transform {
public:
    Transform();

    [[nodiscard]] const Vector3 *getPosition() const {
        return &position;
    }

    [[nodiscard]] const Quaternion *getRotation() const {
        return &rotation;
    }

    [[nodiscard]] const Vector3 *getScale() const {
        return &scale;
    }

    Vector3 getWorldPosition();

    Quaternion getWorldRotation();

    Vector3 getWorldScale();

    void setParent(Transform &newParent);

    void setPosition(const Vector3 &newPosition);

    void setRotation(const Quaternion &newRotation);

    void setRotation(const Vector3 &eulerAngles);

    void setScale(const Vector3 &newScale);

    void translate(const Vector3 &translation);

    void rotate(const Quaternion &angles);

    void rotate(const Vector3 &eulerAngles);

    void scaleBy(const Vector3 &scaling);

    [[nodiscard]] Matrix4x4 getTransformMatrix();

protected:
    ~Transform();

private:
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;

    Matrix4x4 worldMatrix;

    Transform *parent;

    bool isDirty = false;

    void updateWorldMatrix();
    void tryUpdateWorldMatrix();
};
