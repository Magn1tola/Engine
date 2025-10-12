//
// Created by Magnitola on 18.09.2025.
//

#include "./Entity.h"

#include <math/Transform.h>
#include <EntityComponent.h>


Entity::Entity() {
    transform = std::make_shared<Transform>();
}

void Entity::onSpawned() {
}

void Entity::tryUpdate(float deltaTime) {
    if (bCanBeUpdated) update(deltaTime);
    if (bComponentsCanUpdate) {
        for (EntityComponent *component: components_)
            component->tryUpdate(deltaTime);
    }
}

void Entity::update(float deltaTime) {
}


