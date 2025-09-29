//
// Created by Magnitola on 18.09.2025.
//

#include "Transform.h"

#include <format>
#include <stdexcept>
#include <unordered_set>

#include "Matrix4x4.h"
#include "Quaternion.h"
#include "Vector3.h"


Transform::Transform() {
    position = Vector3();
    rotation = Quaternion();
    scale = Vector3(1.0f);
    parent = nullptr;
}

Vector3 Transform::getWorldPosition() {
    tryUpdateWorldMatrix();
    return getTransformMatrix().extractPosition();
}

Quaternion Transform::getWorldRotation() {
    tryUpdateWorldMatrix();
    return getTransformMatrix().extractRotation();
}

Vector3 Transform::getWorldScale() {
    tryUpdateWorldMatrix();
    return getTransformMatrix().extractScale();
}

void Transform::setParent(Transform &newParent) {
    parent = &newParent;
    if (parent == nullptr) {
        worldMatrix = Matrix4x4();
    } else {
        isDirty = true;

        // validate hierarchy
        std::unordered_set<Transform *> visited;
        Transform *iterator = parent;
        while (iterator != nullptr) {
            if (visited.contains(iterator)) {
                throw std::runtime_error(std::format("{} Detected circular parent hierarchy", __PRETTY_FUNCTION__));
            }
            visited.insert(iterator);
            iterator = iterator->parent;
        }
    }
}

void Transform::setPosition(const Vector3 &newPosition) {
    position = newPosition;
    isDirty = true;
}

void Transform::setRotation(const Quaternion &newRotation) {
    rotation = newRotation;
    rotation.normalize();
    isDirty = true;
}

void Transform::setRotation(const Vector3 &eulerAngles) {
    rotation = Quaternion::fromEuler(eulerAngles);
    rotation.normalize();
    isDirty = true;
}

void Transform::setScale(const Vector3 &newScale) {
    scale = newScale;
    isDirty = true;
}

void Transform::translate(const Vector3 &translation) {
    position += translation;
    isDirty = true;
}

void Transform::rotate(const Quaternion &angles) {
    rotation = angles * rotation;
    rotation.normalize();
    isDirty = true;
}

void Transform::rotate(const Vector3 &eulerAngles) {
    const Quaternion newRotation = Quaternion::fromEuler(eulerAngles);
    rotation = newRotation * rotation;
    rotation.normalize();
    isDirty = true;
}

void Transform::scaleBy(const Vector3 &scaling) {
    scale *= scaling;
    isDirty = true;
}

Matrix4x4 Transform::getTransformMatrix() {
    tryUpdateWorldMatrix();
    return Matrix4x4::scale(scale) *
           Matrix4x4::rotation(rotation) *
           Matrix4x4::translation(position) * worldMatrix;
}

Transform::~Transform() = default;

void Transform::updateWorldMatrix() {
    if (parent != nullptr)
        worldMatrix = parent->getTransformMatrix();
    isDirty = false;
}

void Transform::tryUpdateWorldMatrix() {
    if (isDirty || (parent != nullptr && parent->isDirty))
        updateWorldMatrix();
}
