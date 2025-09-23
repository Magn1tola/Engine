//
// Created by Magnitola on 20.09.2025.
//

#pragma once


class Shader;

class Material {
public:
    Material();

    Shader *shader;

protected:
    ~Material();
};
