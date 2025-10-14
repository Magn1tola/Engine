//
// Created by Magnitola on 18.09.2025.
//

#pragma once
#include <memory>
#include <vector>

#include "EngineObject.h"

class Transform;
class World;
class EntityComponent;

class Entity : public EngineObject, public Reflected<Entity> {
    DECLARE_REFLECTED(Entity);
    REFLECTED_BASE(EngineObject);

public:
    Entity();

    ~Entity() override = default;

    std::shared_ptr<Transform> transform;

    [[nodiscard]] std::shared_ptr<World> getWorld() const { return world_; }

    virtual void onSpawned();

    void tryUpdate(float deltaTime);

    FIELD_INIT(int, aaa, 20);

protected:
    bool bCanBeUpdated = false;
    bool bComponentsCanUpdate = true;

    virtual void update(float deltaTime);

    template<class T> requires std::derived_from<T, EntityComponent>
    T *createComponent() {
        T *component = new T();
        components_.push_back(component);
        component->setOwner(this);
        component->onConstructed();
        return component;
    }

private:
    bool isAttached_ = false;
    std::vector<EntityComponent *> components_;

    std::shared_ptr<World> world_;

    friend class World;
};

#define CREATE_SHARED_COMPONENT(type) std::shared_ptr<type>(createComponent<type>())
#define CREATE_UNIQUE_COMPONENT(type) std::unique_ptr<type>(createComponent<type>())
