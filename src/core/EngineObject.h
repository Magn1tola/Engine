//
// Created by Magnitola on 18.09.2025.
//

#pragma once
#include <reflection/Reflector.h>

class EngineObject {
    DECLARE_REFLECTED(EngineObject);

public:
    EngineObject() = default;

    virtual ~EngineObject() = default;

};
