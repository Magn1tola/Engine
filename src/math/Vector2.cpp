//
// Created by Magnitola on 12.10.2025.
//

#include "Vector2.h"

#include <cmath>


Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(const float value) : x(value), y(value) {}

Vector2::Vector2(const float xValue, const float yValue) : x(xValue), y(yValue) {}

Vector2::~Vector2() = default;

float Vector2::GetMagnitude() const {
    return sqrtf(x * x + y * y);
}

void Vector2::normalize() {
    if (const float magnitude = GetMagnitude(); magnitude > 0) {
        x /= magnitude;
        y /= magnitude;
    }
}

float Vector2::cross(const Vector2& lhs, const Vector2& rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

float Vector2::dot(const Vector2& lhs, const Vector2& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2 Vector2::lerp(const Vector2& lhs, const Vector2& rhs, const float t) {
    return lhs + (rhs - lhs) * t;
}

float Vector2::distance(const Vector2& lhs, const Vector2& rhs) {
    return (rhs - lhs).GetMagnitude();
}

Vector2 Vector2::operator+(const Vector2& rhs) const {
    return {x + rhs.x, y + rhs.y};
}

Vector2 Vector2::operator-(const Vector2& rhs) const {
    return {x - rhs.x, y - rhs.y};
}

Vector2 Vector2::operator*(const Vector2& rhs) const {
    return {x * rhs.x, y * rhs.y};
}

Vector2 Vector2::operator/(const Vector2& rhs) const {
    return {x / rhs.x, y / rhs.y};
}

Vector2 Vector2::operator*(const float rhs) const {
    return {x * rhs, y * rhs};
}

Vector2 Vector2::operator/(const float rhs) const {
    return {x / rhs, y / rhs};
}

void Vector2::operator+=(const Vector2& rhs) {
    x += rhs.x;
    y += rhs.y;
}

void Vector2::operator-=(const Vector2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
}

void Vector2::operator*=(const Vector2& rhs) {
    x *= rhs.x;
    y *= rhs.y;
}

void Vector2::operator/=(const Vector2& rhs) {
    x /= rhs.x;
    y /= rhs.y;
}

void Vector2::operator*=(const float rhs) {
    x *= rhs;
    y *= rhs;
}

void Vector2::operator/=(const float rhs) {
    x /= rhs;
    y /= rhs;
}