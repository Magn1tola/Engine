//
// Created by Magnitola on 20.09.2025.
//

#include "Matrix4x4.h"

#include <cmath>
#include <math/Quaternion.h>
#include <math/Vector3.h>

Matrix4x4::Matrix4x4() {
    identity();
}

Matrix4x4::Matrix4x4(float value) {
    for (float & m1 : m) m1 = value;
}

void Matrix4x4::identity() {
    for (float &i: m) i = 0;
    m[0] = m[5] = m[10] = m[15] = 1.0f;
}

Matrix4x4 Matrix4x4::translation(const Vector3 &translation) {
    auto result = Matrix4x4();
    result.m[12] = translation.x;
    result.m[13] = translation.y;
    result.m[14] = translation.z;
    return result;
}

Matrix4x4 Matrix4x4::scale(const Vector3 &scale) {
    auto result = Matrix4x4();
    result.m[0] = scale.x;
    result.m[5] = scale.y;
    result.m[10] = scale.z;
    return result;
}

Matrix4x4 Matrix4x4::rotation(const Quaternion &rotation) {
    auto result = Matrix4x4();

    const float xx = rotation.x * rotation.x;
    const float xy = rotation.x * rotation.y;
    const float xz = rotation.x * rotation.z;
    const float xw = rotation.x * rotation.w;

    const float yy = rotation.y * rotation.y;
    const float yz = rotation.y * rotation.z;
    const float yw = rotation.y * rotation.w;

    const float zz = rotation.z * rotation.z;
    const float zw = rotation.z * rotation.w;

    result.m[0] = 1.0f - 2.0f * (yy + zz);
    result.m[1] = 2.0f * (xy + zw);
    result.m[2] = 2.0f * (xz - yw);

    result.m[4] = 2.0f * (xy - zw);
    result.m[5] = 1.0f - 2.0f * (xx + zz);
    result.m[6] = 2.0f * (yz + xw);

    result.m[8] = 2.0f * (xz + yw);
    result.m[9] = 2.0f * (yz - xw);
    result.m[10] = 1.0f - 2.0f * (xx + yy);

    return result;
}

Matrix4x4 Matrix4x4::perspective(float fov, float aspect, float near, float far) {
    auto result = Matrix4x4();

    const float f = 1.0f / tanf(fov * 0.5f * (3.14159f / 180.0f));
    const float range = near - far;

    result.m[0] = f / aspect;
    result.m[5] = f;
    result.m[10] = (far + near) / range;
    result.m[11] = -1.0f;
    result.m[14] = (2.0f * far * near) / range;
    result.m[15] = 0.0f;

    return result;
}

Matrix4x4 Matrix4x4::orthographic(float left, float right, float bottom, float top, float near, float far) {
    auto result = Matrix4x4();

    result.m[0] = 2.0f / (right - left);
    result.m[5] = 2.0f / (top - bottom);
    result.m[10] = -2.0f / (far - near);

    result.m[12] = -(right + left) / (right - left);
    result.m[13] = -(top + bottom) / (top - bottom);
    result.m[14] = -(far + near) / (far - near);

    return result;
}

Matrix4x4 Matrix4x4::lookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up) {
    Matrix4x4 result;

    Vector3 zAxis = (target - eye);
    zAxis.normalize();

    Vector3 xAxis = Vector3::cross(up, zAxis);
    xAxis.normalize();

    const Vector3 yAxis = Vector3::cross(zAxis, xAxis);

    result.m[0] = xAxis.x;
    result.m[1] = yAxis.x;
    result.m[2] = zAxis.x;
    result.m[3] = 0.0f;

    result.m[4] = xAxis.y;
    result.m[5] = yAxis.y;
    result.m[6] = zAxis.y;
    result.m[7] = 0.0f;

    result.m[8] = xAxis.z;
    result.m[9] = yAxis.z;
    result.m[10] = zAxis.z;
    result.m[11] = 0.0f;

    result.m[12] = -Vector3::dot(xAxis, eye);
    result.m[13] = -Vector3::dot(yAxis, eye);
    result.m[14] = -Vector3::dot(zAxis, eye);
    result.m[15] = 1.0f;

    return result;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &rhs) const {
    auto result = Matrix4x4();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i * 4 + j] = 0;
            for (int k = 0; k < 4; k++) {
                result.m[i * 4 + j] += m[i * 4 + k] * rhs.m[k * 4 + j];
            }
        }
    }
    return result;
}

Matrix4x4 &Matrix4x4::operator*=(const Matrix4x4 &rhs) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i * 4 + j] = 0;
            for (int k = 0; k < 4; k++) {
                m[i * 4 + j] += m[i * 4 + k] * rhs.m[k * 4 + j];
            }
        }
    }
    return *this;
}

const float *Matrix4x4::getData() const {
    return m;
}
