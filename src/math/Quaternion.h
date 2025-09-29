//
// Created by Magnitola on 20.09.2025.
//

#pragma once


class Vector3;
class Matrix4x4;

class Quaternion {
public:
    float x, y, z, w;

    Quaternion();

    Quaternion(float x, float y, float z, float w);

    static Quaternion fromAngleAxis(float angle, const Vector3 &axis);

    static Quaternion fromEuler(const Vector3 &euler);

    static Quaternion FromEuler(float pitch, float yaw, float roll);

    void normalize();

    [[nodiscard]] Quaternion conjugate() const;

    [[nodiscard]] Vector3 rotateVector(const Vector3 &vector) const;

    [[nodiscard]] Vector3 toEuler() const;

    void rotateByEuler(const Vector3 &euler);

    Quaternion operator*(const Quaternion &rhs) const;

    Quaternion &operator*=(const Quaternion &rhs);
};
