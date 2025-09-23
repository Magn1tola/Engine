//
// Created by Magnitola on 18.09.2025.
//

#pragma once
#include <memory>
#include <ranges>
#include <vector>

#include "math/Transform.h"


class Entity;
class Transform;
class Render;

class World {
public:
    World();

    ~World();

    [[nodiscard]] Render *getRender() const;

    void update(float deltaTime) const;

    template<class T>
        requires std::derived_from<T, Entity>
    T *spawnEntity();

    template<class T>
        requires std::derived_from<T, Entity>
    T *spawnEntity(Transform *transform);

private:
    std::unique_ptr<Render> render_;

    std::vector<Entity *> entities_;

    void initEntity(Entity *entity);
};

template<class T> requires std::derived_from<T, Entity>
T *World::spawnEntity() {
    T *entity = new T();
    initEntity(entity);
    return entity;
}

template<class T> requires std::derived_from<T, Entity>
T *World::spawnEntity(Transform *transform) {
    T *entity = new T();
    initEntity(entity, transform);
    return entity;
}
