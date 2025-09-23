//
// Created by Magnitola on 20.09.2025.
//

#include "Quaternion.h"

#include <cmath>

#include "math/Vector3.h"

Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {
}

Quaternion::Quaternion(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {
}

Quaternion Quaternion::fromAngleAxis(const float angle, const Vector3 &axis) {
    const float halfAngle = angle * 0.5f;
    const float sinHalf = sinf(halfAngle);
    return Quaternion{
        axis.x * sinHalf,
        axis.y * sinHalf,
        axis.z * sinHalf,
        cosf(halfAngle)
    };
}

Quaternion Quaternion::fromEuler(const Vector3 &euler) {
    return FromEuler(euler.x, euler.y, euler.z);
}

Quaternion Quaternion::FromEuler(float pitch, float yaw, float roll) {
    pitch = pitch * 0.5f * (3.14159f / 180.0f);
    yaw = yaw * 0.5f * (3.14159f / 180.0f);
    roll = roll * 0.5f * (3.14159f / 180.0f);

    const float sinP = sinf(pitch);
    const float cosP = cosf(pitch);
    const float sinY = sinf(yaw);
    const float cosY = cosf(yaw);
    const float sinR = sinf(roll);
    const float cosR = cosf(roll);

    return Quaternion{
        sinR * cosP * cosY - cosR * sinP * sinY,
        cosR * sinP * cosY + sinR * cosP * sinY,
        cosR * cosP * sinY - sinR * sinP * cosY,
        cosR * cosP * cosY + sinR * sinP * sinY
    };
}

void Quaternion::normalize() {
    if (const float magnitude = sqrtf(x * x + y * y + z * z + w * w); magnitude > 0) {
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
        w /= magnitude;
    }
}

Quaternion Quaternion::conjugate() const {
    return Quaternion{-x, -y, -z, w};
}

void Quaternion::rotateByEuler(const Vector3 &euler) {
    Quaternion rotation = fromEuler(euler);
    *this = rotation * (*this);
    normalize();
}

Quaternion Quaternion::operator*(const Quaternion &rhs) const {
    return Quaternion{
        w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
        w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x,
        w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w,
        w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z
    };
}

Quaternion & Quaternion::operator*=(const Quaternion &rhs) {
    *this = *this * rhs;
    normalize();
    return *this;
}

Vector3 Quaternion::rotateVector(const Vector3 &vector) const {
    const Quaternion vectorQuat(vector.x, vector.y, vector.z, 0);
    const Quaternion result = *this * vectorQuat * conjugate();
    return Vector3{result.x, result.y, result.z};
}

Vector3 Quaternion::toEuler() const {
    Quaternion q = *this;
    q.normalize();

    float sinP = 2.0f * (q.w * q.y - q.z * q.x);

    float pitch, yaw, roll;

    if (std::fabs(sinP) >= 0.9999f) {
        pitch = std::copysign(3.14159f / 2.0f, sinP);
        yaw = atan2f(2.0f * (q.w * q.z + q.x * q.y),
                      1.0f - 2.0f * (q.y * q.y + q.z * q.z));
        roll = 0;
    } else {
        pitch = asinf(sinP);
        yaw = atan2f(2.0f * (q.w * q.z + q.x * q.y),
                      1.0f - 2.0f * (q.x * q.x + q.z * q.z));
        roll = atan2f(2.0f * (q.w * q.x + q.y * q.z),
                      1.0f - 2.0f * (q.x * q.x + q.y * q.y));
    }

    constexpr float radToDeg = 180.0f / 3.14159f;
    return {
        pitch * radToDeg,
        yaw * radToDeg,
        roll * radToDeg
    };
}