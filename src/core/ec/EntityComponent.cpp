//
// Created by Magnitola on 18.09.2025.
//

#include "EntityComponent.h"

#include "Entity.h"

EntityComponent::EntityComponent() {
    owner_ = nullptr;
}

void EntityComponent::onConstructed() {
}

void EntityComponent::tryUpdate(float deltaTime) {
    if (bCanBeUpdated) update(deltaTime);
}

void EntityComponent::setOwner(Entity *newOwner) {
    owner_ = newOwner;
}

void EntityComponent::update(float deltaTime) {
}
