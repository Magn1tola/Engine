//
// Created by Magnitola on 18.09.2025.
//

#include "./World.h"

#include <Entity.h>
#include <render/Render.h>

World::World() {
    render_ = std::make_unique<Render>();
}

World::~World() = default;

Render *World::getRender() const {
    return render_.get();
}

void World::update(float deltaTime) const {
    for (Entity *entity: entities_) {
        entity->tryUpdate(deltaTime);
    }
}

void World::initEntity(Entity *entity) {
    entities_.push_back(entity);
    entity->world = this;
    entity->onSpawned();
}
