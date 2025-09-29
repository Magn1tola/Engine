//
// Created by Magnitola on 20.09.2025.
//

#pragma once


class Quaternion;
class Vector3;

class Matrix4x4 {
public:
    Matrix4x4();

    explicit Matrix4x4(float value);

    float m[16];

    void identity();

    [[nodiscard]] Vector3 extractPosition() const;
    [[nodiscard]] Quaternion extractRotation() const;
    [[nodiscard]] Vector3 extractScale() const;

    static Matrix4x4 translation(const Vector3 &translation);

    static Matrix4x4 scale(const Vector3 &scale);

    static Matrix4x4 rotation(const Quaternion &rotation);

    static Matrix4x4 perspective(float fov, float aspect, float near, float far);

    static Matrix4x4 orthographic(float left, float right, float bottom, float top, float near, float far);

    static Matrix4x4 lookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up);

    [[nodiscard]] const float *getData() const;

    Matrix4x4 operator*(const Matrix4x4 &rhs) const;

    Matrix4x4& operator*=(const Matrix4x4 &rhs);
};
