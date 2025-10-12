//
// Created by Magnitola on 12.10.2025.
//

#pragma once
#include <vector>

#include "AssetLoader.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "render/Model.h"


class ModelAssetLoader : public AssetLoader {
public:
    std::unique_ptr<Asset> load(std::string_view path) override;

    ~ModelAssetLoader() override = default;

private:
    std::vector<Vector3> vertPoses_;
    std::vector<Vector3> normals_;
    std::vector<Vector2> texCoords_;
    std::vector<Vertex> vertexes_;
    std::vector<unsigned int> indices_;

    void parseVertPose(std::string_view line);
    void parseNormal(std::string_view line);
    void parseTexCoord(std::string_view line);

    void parseFace(std::string_view line);
};
