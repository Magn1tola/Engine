//
// Created by Magnitola on 18.09.2025.
//

#pragma once

#include "EngineObject.h"

class Entity;

class EntityComponent : public EngineObject {
public:
    EntityComponent();

    ~EntityComponent() override = default;

    [[nodiscard]] Entity *getOwner() const { return owner_; }

    virtual void onConstructed();

    void tryUpdate(float deltaTime);

    virtual void setOwner(Entity *newOwner);

    bool bCanBeUpdated = false;

    virtual void update(float deltaTime);

private:
    Entity *owner_;

    BEGIN_REFLECTED_TYPE(EntityComponent)
        BASE_TYPE(EngineObject)
        CONSTRUCTOR()
        FIELD(bCanBeUpdated)
        FIELD(owner_)
    END_REFLECTED_TYPE();
};
