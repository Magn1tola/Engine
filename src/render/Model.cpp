//
// Created by Magnitola on 19.09.2025.
//

#include "Model.h"

#include <GL/glew.h>

Model::Model() : vao(0), vbo(0), ebo(0), elementsCount(0) {
}

Model::~Model() {
    unload();
}

void Model::load(const std::vector<Vertex> &data, const std::vector<unsigned int> &indices, const std::string &modelName) {
    name = modelName;
    if (vao == 0)
        glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    constexpr size_t vertexSize = sizeof(Vertex);

    if (vbo == 0)
        glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * vertexSize, data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<void *>(offsetof(Vertex, normal)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<void *>(offsetof(Vertex, texCoords)));
    glEnableVertexAttribArray(2);

    elementsCount = indices.size();

    if (ebo == 0)
        glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsCount * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Model::unload() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}
