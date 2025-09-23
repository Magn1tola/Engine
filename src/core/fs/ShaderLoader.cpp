//
// Created by Magnitola on 17.09.2025.
//

#include "ShaderLoader.h"

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

GLuint ShaderLoader::createShaderProgram(const char *name, const char *directory) {
    std::string pathVert = std::format("{}/{}.vert", directory, name);
    std::string pathFrag = std::format("{}/{}.frag", directory, name);

    const GLuint vertexShader = createShader(GL_VERTEX_SHADER, pathVert);
    const GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, pathFrag);
    const GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint result = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    int infoLogLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

    // Logging shader program linking errors in console
    if (infoLogLength > 0) {
        char *errorMessage = new char[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, nullptr, errorMessage);
        std::cout << errorMessage;
        delete[] errorMessage;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

std::string ShaderLoader::readFile(const char *path) {
    std::string text;

    // Convert local path to absolute
    std::filesystem::path paths = std::filesystem::absolute(path);

    if (std::ifstream file(paths.string(), std::ios::in); file.is_open()) {
        std::stringstream sstr;
        sstr << file.rdbuf();
        text = sstr.str();
        file.close();
    }

    if (text.empty()) {
        std::cout << "Failed to read file " << path << std::endl;
    }

    return text;
}

GLuint ShaderLoader::createShader(const GLenum shaderType, const std::string &source) {
    const GLuint shaderId = glCreateShader(shaderType);
    const std::string shaderSource = readFile(source.c_str());
    const char *pointer = shaderSource.c_str();

    glShaderSource(shaderId, 1, &pointer, nullptr);
    glCompileShader(shaderId);

    GLint result;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    int infoLogLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

    // Logging shader compilation errors in console
    if (infoLogLength > 0) {
        char *errorMessage = new char[infoLogLength + 1];
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, errorMessage);
        std::cout << errorMessage;
        delete[] errorMessage;
    }

    return shaderId;
}
