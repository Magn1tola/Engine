//
// Created by Magnitola on 12.10.2025.
//

#pragma once


class Vector2 {
public:
    Vector2();

    explicit Vector2(float value);

    Vector2(float xValue, float yValue);

    ~Vector2();

    float x;
    float y;

    [[nodiscard]] float GetMagnitude() const;

    void normalize();

    static float cross(const Vector2 &lhs, const Vector2 &rhs);

    static float dot(const Vector2 &lhs, const Vector2 &rhs);

    static Vector2 lerp(const Vector2 &lhs, const Vector2 &rhs, float t);

    static float distance(const Vector2 &lhs, const Vector2 &rhs);

    Vector2 operator+(const Vector2 &rhs) const;

    Vector2 operator-(const Vector2 &rhs) const;

    Vector2 operator*(const Vector2 &rhs) const;

    Vector2 operator/(const Vector2 &rhs) const;

    Vector2 operator*(float rhs) const;

    Vector2 operator/(float rhs) const;

    void operator+=(const Vector2 &rhs);

    void operator-=(const Vector2 &rhs);

    void operator*=(const Vector2 &rhs);

    void operator/=(const Vector2 &rhs);

    void operator*=(float rhs);

    void operator/=(float rhs);
};
