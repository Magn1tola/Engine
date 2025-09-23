//
// Created by Magnitola on 18.09.2025.
//

#include "Transform.h"

#include "Matrix4x4.h"
#include "Quaternion.h"
#include "Vector3.h"


Transform::Transform() {
    position = new Vector3();
    rotation = new Quaternion();
    scale = new Vector3(1.0f);
}

void Transform::setPosition(const Vector3& newPosition) const {
    *position = newPosition;
}

void Transform::setRotation(const Quaternion& newRotation) const {
    *rotation = newRotation;
    rotation->normalize();
}

void Transform::setRotation(const Vector3& eulerAngles) const {
    *rotation = Quaternion::fromEuler(eulerAngles);
    rotation->normalize();
}

void Transform::setScale(const Vector3& newScale) const {
    *scale = newScale;
}

void Transform::translate(const Vector3& translation) const {
    *position += translation;
}

void Transform::rotate(const Quaternion& rotation) const {
    *this->rotation = rotation * *this->rotation;
    this->rotation->normalize();
}

void Transform::rotate(const Vector3& eulerAngles) const {
    const Quaternion newRotation = Quaternion::fromEuler(eulerAngles);
    *rotation = newRotation * *rotation;
    rotation->normalize();
}

void Transform::scaleBy(const Vector3& scaling) const {
    *scale *= scaling;
}

Matrix4x4 Transform::getTransformMatrix() const {
    return Matrix4x4::scale(*scale) *
           Matrix4x4::rotation(*rotation) *
           Matrix4x4::translation(*position);
}

Transform::~Transform() {
    delete position;
    delete rotation;
    delete scale;
}
