//
// Created by Magnitola on 18.09.2025.
//

#pragma once

class Matrix4x4;
struct Vector3;
struct Quaternion;

class Transform {
public:
    Transform();

    Vector3 *position;
    Quaternion *rotation;
    Vector3 *scale;

    void setPosition(const Vector3 &newPosition) const;

    void setRotation(const Quaternion &newRotation) const;

    void setRotation(const Vector3 &eulerAngles) const;

    void setScale(const Vector3 &newScale) const;

    void translate(const Vector3 &translation) const;

    void rotate(const Quaternion &rotation) const;

    void rotate(const Vector3 &eulerAngles) const;

    void scaleBy(const Vector3 &scaling) const;

    [[nodiscard]] Matrix4x4 getTransformMatrix() const;

protected:
    ~Transform();
};
