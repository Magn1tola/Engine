//
// Created by Magnitola on 17.09.2025.
//

#pragma once

#include <string>
#include <GL/glew.h>


class ShaderLoader {
public:

    /**
     * Find [name].vert [name].frag files in [directory] and create shader program
     * @param name shader name
     * @param directory shader directory
     * @return GLuint shader id
     */
    static GLuint createShaderProgram(const char *name, const char *directory);

private:
    static std::string readFile(const char *path);

    static GLuint createShader(GLenum shaderType, const std::string &source);
};
