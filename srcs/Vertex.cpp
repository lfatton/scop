#include "Vertex.hpp"

Vertex::Vertex() {
    initObjects();
}

Vertex::~Vertex() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Vertex::initObjects() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}