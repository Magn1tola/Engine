//
// Created by Magnitola on 18.09.2025.
//

#pragma once
#include "../reflection/Reflected.h"

class EngineObject : public Reflected<EngineObject> {
    DECLARE_REFLECTED(EngineObject);

public:
    EngineObject() = default;

    virtual ~EngineObject() = default;

    FIELD_INIT(int, test, 10);
};
