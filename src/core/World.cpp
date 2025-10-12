//
// Created by Magnitola on 18.09.2025.
//

#include "World.h"

#include "Entity.h"

void World::update(float deltaTime) const {
    for (const auto& entity: entities_) {
        entity->tryUpdate(deltaTime);
    }
}
