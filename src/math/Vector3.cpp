//
// Created by Magnitola on 18.09.2025.
//

#include "Vector3.h"

#include <cmath>

Vector3::Vector3() {
    x = y = z = 0;
}

Vector3::~Vector3() = default;

float Vector3::GetMagnitude() const {
    return sqrtf(x*x + y*y + z*z);
}

void Vector3::normalize() {
    if (const float magnitude = this->GetMagnitude(); magnitude > 0) {
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
    }
}

Vector3 Vector3::cross(const Vector3 &lhs, const Vector3 &rhs) {
    Vector3 result;
    result.x = lhs.y * rhs.z - lhs.z * rhs.y;
    result.y = lhs.z * rhs.x - lhs.x * rhs.z;
    result.z = lhs.x * rhs.y - lhs.y * rhs.x;
    return result;
}

float Vector3::dot(const Vector3 &lhs, const Vector3 &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::lerp(const Vector3 &lhs, const Vector3 &rhs, float t) {
    return lhs + (rhs - lhs) * t;
}

float Vector3::distance(const Vector3 &lhs, const Vector3 &rhs) {
    return (rhs - lhs).GetMagnitude();
}

Vector3 Vector3::operator+(const Vector3 &rhs) const {
    return Vector3{this->x + rhs.x, this->y + rhs.y, this->z + rhs.z};
}

Vector3 Vector3::operator-(const Vector3 &rhs) const {
    return Vector3{this->x - rhs.x, this->y - rhs.y, this->z - rhs.z};
}

Vector3 Vector3::operator*(const Vector3 &rhs) const {
    return Vector3{this->x * rhs.x, this->y * rhs.y, this->z * rhs.z};
}

Vector3 Vector3::operator/(const Vector3 &rhs) const {
    return Vector3{this->x / rhs.x, this->y / rhs.y, this->z / rhs.z};
}

Vector3 Vector3::operator*(const float rhs) const {
    return Vector3{this->x * rhs, this->y * rhs, this->z * rhs};
}

Vector3 Vector3::operator/(const float rhs) const {
    return Vector3{this->x / rhs, this->y / rhs, this->z / rhs};
}

void Vector3::operator+=(const Vector3 &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
}

void Vector3::operator-=(const Vector3 &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
}

void Vector3::operator*=(const Vector3 &rhs) {
    this->x *= rhs.x;
    this->y *= rhs.y;
    this->z *= rhs.z;
}

void Vector3::operator/=(const Vector3 &rhs) {
    this->x /= rhs.x;
    this->y /= rhs.y;
    this->z /= rhs.z;
}

void Vector3::operator*=(const float rhs) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
}

void Vector3::operator/=(const float rhs) {
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
}
