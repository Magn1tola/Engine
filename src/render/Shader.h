//
// Created by Magnitola on 20.09.2025.
//

#pragma once


class Shader {
public:
    Shader();

    unsigned int programId;
    unsigned int vpUniformPos;
    unsigned int modelUniformPos;

protected:
    ~Shader();
};
