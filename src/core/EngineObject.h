//
// Created by Magnitola on 18.09.2025.
//

#pragma once
#include <reflection/Reflector.h>

class EngineObject {
public:
    EngineObject() = default;

    virtual ~EngineObject() = default;

    BEGIN_REFLECTED_TYPE(EngineObject)
        CONSTRUCTOR()
    END_REFLECTED_TYPE();
};
