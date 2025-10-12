//
// Created by Magnitola on 12.10.2025.
//

#include "ModelAssetLoader.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ranges>

#include <string>
#include <string_view>
#include <vector>

std::unique_ptr<Asset> ModelAssetLoader::load(std::string_view path) {
    const std::filesystem::path paths = std::filesystem::absolute(path);
    if (std::ifstream file(paths.string()); file.is_open()) {
        vertPoses_.clear();
        normals_.clear();
        texCoords_.clear();
        vertexes_.clear();
        indices_.clear();

        std::string line;
        while (std::getline(file, line)) {
            std::string_view sv(line);
            if (sv.empty() || sv.starts_with("#")) continue;
            else if (sv.starts_with("v "))
                parseVertPose(sv);
            else if (sv.starts_with("vn "))
                parseNormal(sv);
            else if (sv.starts_with("vt "))
                parseTexCoord(sv);
            else if (sv.starts_with("f "))
                parseFace(sv);
        }

        auto result = std::make_unique<Model>();
        result->vertices_ = std::move(vertexes_);
        result->indices_ = std::move(indices_);
        return result;
    }
    return nullptr;
}

void ModelAssetLoader::parseVertPose(std::string_view line) {
    Vector3 vector;
    if (sscanf(line.data(), "v %f %f %f", &vector.x, &vector.y, &vector.z) == 3) {
        vertPoses_.push_back(vector);
    }
}

void ModelAssetLoader::parseNormal(std::string_view line) {
    Vector3 vector;
    if (sscanf(line.data(), "vn %f %f %f", &vector.x, &vector.y, &vector.z) == 3) {
        normals_.push_back(vector);
    }
}

void ModelAssetLoader::parseTexCoord(std::string_view line) {
    Vector2 vector;
    if (sscanf(line.data(), "vt %f %f", &vector.x, &vector.y) == 2) {
        texCoords_.push_back(vector);
    }
}

void ModelAssetLoader::parseFace(std::string_view line) {
    std::istringstream iss(line.data());
    std::string token;

    iss >> token;

    while (iss >> token) {
        std::ranges::replace(token, '/', ' ');

        std::istringstream token_stream(token);
        unsigned int p, n, u;
        token_stream >> p >> u >> n;
        Vertex vertex;
        vertex.position = vertPoses_[p - 1],
        vertex.texCoords = texCoords_[u - 1],
        vertex.normal = normals_[n - 1],
        vertexes_.push_back(vertex);
        indices_.push_back(vertexes_.size() - 1);
    }
}
