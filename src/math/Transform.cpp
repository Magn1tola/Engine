//
// Created by Magnitola on 18.09.2025.
//

#include "Transform.h"

#include <format>
#include <stdexcept>
#include <unordered_set>
#include <utility>

#include "Matrix4x4.h"
#include "Quaternion.h"
#include "Vector3.h"


Transform::Transform() {
    position_ = Vector3();
    rotation_ = Quaternion();
    scale_ = Vector3(1.0f);
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

void Transform::attachTo(const std::shared_ptr<Transform> &newParent) {
    if (parent_.lock() == newParent) return;

    if (newParent) {
        // validate hierarchy
        std::unordered_set<Transform *> visited;
        visited.insert(this);
        Transform *iterator = newParent.get();
        while (iterator != nullptr) {
            if (visited.contains(iterator)) {
                throw std::runtime_error(std::format("{} Detected circular parent hierarchy", __PRETTY_FUNCTION__));
            }
            visited.insert(iterator);

            std::shared_ptr<Transform> locked = iterator->parent_.lock();
            iterator = locked ? locked.get() : nullptr;
        }
    }

    parent_ = newParent;
    if (newParent) {
        isDirty = true;
    } else {
        worldMatrix_ = Matrix4x4();
    }
}

void Transform::setPosition(const Vector3 &newPosition) {
    position_ = newPosition;
    isDirty = true;
}

void Transform::setRotation(const Quaternion &newRotation) {
    rotation_ = newRotation;
    rotation_.normalize();
    isDirty = true;
}

void Transform::setRotation(const Vector3 &eulerAngles) {
    rotation_ = Quaternion::fromEuler(eulerAngles);
    rotation_.normalize();
    isDirty = true;
}

void Transform::setScale(const Vector3 &newScale) {
    scale_ = newScale;
    isDirty = true;
}

void Transform::translate(const Vector3 &translation) {
    position_ += translation;
    isDirty = true;
}

void Transform::rotate(const Quaternion &angles) {
    rotation_ = angles * rotation_;
    rotation_.normalize();
    isDirty = true;
}

void Transform::rotate(const Vector3 &eulerAngles) {
    const Quaternion newRotation = Quaternion::fromEuler(eulerAngles);
    rotation_ = newRotation * rotation_;
    rotation_.normalize();
    isDirty = true;
}

void Transform::scaleBy(const Vector3 &scaling) {
    scale_ *= scaling;
    isDirty = true;
}

Matrix4x4 Transform::getTransformMatrix() {
    tryUpdateWorldMatrix();
    return Matrix4x4::scale(scale_) *
           Matrix4x4::rotation(rotation_) *
           Matrix4x4::translation(position_) * worldMatrix_;
}

Transform::~Transform() = default;

void Transform::updateWorldMatrix() {
    if (parent_.lock() != nullptr)
        worldMatrix_ = parent_.lock()->getTransformMatrix();
    isDirty = false;
}

void Transform::tryUpdateWorldMatrix() {
    if (isDirty || (parent_.lock() != nullptr && parent_.lock()->isDirty))
        updateWorldMatrix();
}
