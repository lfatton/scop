#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Face> indices): vertices(vertices), indices(indices) {
    for (auto & vertex : vertices)
    {
        this->mVerticesToArray.push_back(vertex.position.x);
        this->mVerticesToArray.push_back(vertex.position.y);
        this->mVerticesToArray.push_back(vertex.position.z);

        if (vertex.textureCoordinates != Vector(0.f, 0.f, 0.f, 1.f)) {
            this->mVerticesToArray.push_back(vertex.textureCoordinates.x);
            this->mVerticesToArray.push_back(vertex.textureCoordinates.y);
        } else {
            this->mVerticesToArray.push_back(1.f);
            this->mVerticesToArray.push_back(0.f);
        }

        if (vertex.normal != Vector(0.f, 0.f, 0.f, 1.f)) {
            this->mVerticesToArray.push_back(vertex.textureCoordinates.x);
            this->mVerticesToArray.push_back(vertex.textureCoordinates.y);
            this->mVerticesToArray.push_back(vertex.textureCoordinates.z);
        }  else {
            this->mVerticesToArray.push_back(0.f);
            this->mVerticesToArray.push_back(1.f);
            this->mVerticesToArray.push_back(0.f);
        }
    }

    for (auto & index : indices)
    {
        this->mIndicesToArray.push_back(index.a - 1);
        this->mIndicesToArray.push_back(index.b - 1);
        this->mIndicesToArray.push_back(index.c - 1);
        if (index.d > 0)
            this->mIndicesToArray.push_back(index.d - 1);
    }

    glGenVertexArrays(1, &(this->mVAO));
    glGenBuffers(1, &(this->mVBO));
    glGenBuffers(1, &(this->mEBO));

    glBindVertexArray(this->mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float),
                 &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 4 * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));

    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mEBO);
}

void Mesh::Draw() {
    glBindVertexArray(this->mVAO);
    glDrawElements(GL_TRIANGLES, this->mIndicesToArray.size(), GL_UNSIGNED_INT, nullptr);
}