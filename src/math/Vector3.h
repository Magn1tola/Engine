//
// Created by Magnitola on 18.09.2025.
//

#pragma once

struct  Vector3 {
    Vector3();

    explicit Vector3(const float value)
        : x(value), y(value), z(value) {
    }

    Vector3(const float xValue, const float yValue, const float zValue)
        : x(xValue), y(yValue), z(zValue) {
    }

    ~Vector3();

    float x;
    float y;
    float z;

    [[nodiscard]] float GetMagnitude() const;

    void normalize();

    static Vector3 cross(const Vector3 &lhs, const Vector3 &rhs);

    static float dot(const Vector3 &lhs, const Vector3 &rhs);

    static Vector3 lerp(const Vector3 &lhs, const Vector3 &rhs, float t);

    static float distance(const Vector3 &lhs, const Vector3 &rhs);

    Vector3 operator+(const Vector3 &rhs) const;

    Vector3 operator-(const Vector3 &rhs) const;

    Vector3 operator*(const Vector3 &rhs) const;

    Vector3 operator/(const Vector3 &rhs) const;

    Vector3 operator*(float rhs) const;

    Vector3 operator/(float rhs) const;

    void operator+=(const Vector3 &rhs);

    void operator-=(const Vector3 &rhs);

    void operator*=(const Vector3 &rhs);

    void operator/=(const Vector3 &rhs);

    void operator*=(float rhs);

    void operator/=(float rhs);
};
