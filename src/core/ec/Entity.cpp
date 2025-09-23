//
// Created by Magnitola on 18.09.2025.
//

#include "./Entity.h"

#include <math/Transform.h>
#include <EntityComponent.h>

Entity::Entity() {
    world = nullptr;
    transform = new Transform();
}

void Entity::onSpawned() {
}

void Entity::tryUpdate(float deltaTime) {
    if (bCanBeUpdated) update(deltaTime);
    if (bComponentsCanUpdate) {
        for (EntityComponent *component: _components)
            component->tryUpdate(deltaTime);
    }
}

void Entity::update(float deltaTime) {
}

void Entity::initComponent(EntityComponent *component) {
    _components.push_back(component);
    component->setOwner(*this);
    component->onConstructed();
}


