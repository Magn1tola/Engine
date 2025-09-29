//
// Created by Magnitola on 21.09.2025.
//

#include "WorldComponent.h"

#include "Entity.h"
#include "math/Transform.h"

WorldComponent::WorldComponent() {
    transform = new Transform();
}

void WorldComponent::setOwner(Entity &newOwner) {
    EntityComponent::setOwner(newOwner);
    transform->setParent(*newOwner.transform);
}
