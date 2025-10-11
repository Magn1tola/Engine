//
// Created by Magnitola on 20.09.2025.
//

#include "Shader.h"

#include <iostream>
#include <GL/glew.h>

#include "math/Matrix4x4.h"
#include "math/Vector3.h"

void Shader::use() const {
    glUseProgram(programId_);
}

void Shader::set_uniform(const std::string &name, const int value) {
    glUniform1i(findUniform(name), value);
}

void Shader::set_uniform(const std::string &name, const float value) {
    glUniform1f(findUniform(name), value);
}

void Shader::set_uniform(const std::string &name, const Vector3 &vector) {
    glUniform3f(findUniform(name), vector.x, vector.y, vector.z);
}

void Shader::set_uniform(const std::string &name, const Matrix4x4 &matrix) {
    glUniformMatrix4fv(findUniform(name), 1, GL_FALSE, matrix.getData());
}

bool Shader::load_impl() {
    return programId_ != 0;
}

void Shader::unload_impl() {
    if (programId_ != 0) {
        glDeleteProgram(programId_);
        programId_ = 0;
    }
}

int Shader::findUniform(const std::string &name) {
    if (const auto it = uniforms_.find(name); it != uniforms_.end()) {
        return it->second;
    }

    const int loc = glGetUniformLocation(programId_, name.c_str());
    uniforms_[name] = loc;
    return loc;
}
