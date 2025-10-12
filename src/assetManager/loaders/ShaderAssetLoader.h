//
// Created by Magnitola on 17.09.2025.
//

#pragma once

#include <string>
#include <GL/glew.h>

#include "../AssetLoader.h"


class ShaderAssetLoader : public AssetLoader {
public:
    std::unique_ptr<Asset> load(std::string_view path) override;

private:
    static GLuint createShaderProgram(const char *name, const char *directory);

    static std::string readFile(const char *path);

    static GLuint createShader(GLenum shaderType, const std::string &source);
};
