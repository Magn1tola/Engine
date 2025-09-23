//
// Created by Magnitola on 18.09.2025.
//

#pragma once
#include "../EngineObject.h"

class Entity;

class EntityComponent : public EngineObject {
public:
    EntityComponent();

    Entity *owner;

    virtual void onConstructed();

    void tryUpdate(float deltaTime);

    virtual void setOwner(Entity &newOwner);

protected:
    ~EntityComponent();

    bool bCanBeUpdated = false;

    virtual void update(float deltaTime);

private:
    typedef EngineObject super;
};
