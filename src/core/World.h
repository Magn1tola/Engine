//
// Created by Magnitola on 18.09.2025.
//

#pragma once
#include <memory>
#include <ranges>
#include <vector>

class Entity;
class Transform;
class Render;

class World : public std::enable_shared_from_this<World> {
public:
    World() = default;

    ~World() = default;

    void update(float deltaTime) const;

    template<class T> requires std::derived_from<T, Entity>
    std::shared_ptr<T> spawnEntity() {
        std::shared_ptr<T> entity = std::make_shared<T>();
        entities_.push_back(entity);
        entity->world_ = shared_from_this();
        entity->onSpawned();
        return entity;
    }

private:
    std::vector<std::shared_ptr<Entity>> entities_;
};