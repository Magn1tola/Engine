//
// Created by Magnitola on 17.09.2025.
//

#include "ShaderAssetLoader.h"

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "render/Shader.h"

std::unique_ptr<Asset> ShaderAssetLoader::load(std::string_view path) {
    std::string path_str(path);
    const size_t separator_pos = path_str.find('|');

    if (separator_pos == std::string::npos) {
        std::cerr << std::format("Invalid shader path format: {}\n", path);
        return nullptr;
    }

    const std::string shader_name = path_str.substr(0, separator_pos);
    const std::string directory = path_str.substr(separator_pos + 1);
    const GLuint program = createShaderProgram(shader_name.c_str(), directory.c_str());
    if (program == 0) {
        return nullptr;
    }

    auto shader = std::make_unique<Shader>();
    shader->path_ = path;
    shader->programId_ = program;
    return shader;
}

GLuint ShaderAssetLoader::createShaderProgram(const char *name, const char *directory) {
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

std::string ShaderAssetLoader::readFile(const char *path) {
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

GLuint ShaderAssetLoader::createShader(const GLenum shaderType, const std::string &source) {
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
