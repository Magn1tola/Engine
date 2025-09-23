//
// Created by Magnitola on 18.09.2025.
//

#pragma once
#include <vector>

#include "EngineObject.h"

class Transform;
class World;
class EntityComponent;

class Entity : public EngineObject {
public:
    Entity();

    Transform* transform;

    World* world;

    virtual void onSpawned();

    void tryUpdate(float deltaTime);

protected:
    ~Entity() = default;

    bool bCanBeUpdated = false;
    bool bComponentsCanUpdate = true;

    virtual void update(float deltaTime);

    template<class T>
        requires std::derived_from<T, EntityComponent>
    T *createComponent();

private:
    bool isAttached_ = false;
    std::vector<EntityComponent *> _components;

    void initComponent(EntityComponent *component);
};

template<class T>
    requires std::derived_from<T, EntityComponent>
T *Entity::createComponent() {
    T *component = new T();
    initComponent(component);
    return component;
}
