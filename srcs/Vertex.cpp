#include "Vertex.hpp"

Vertex::Vertex() {
    initVBO();
    initVAO();
}

Vertex::~Vertex() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
}

unsigned int Vertex::getVAO() {
    return mVAO;
}

void Vertex::initVBO() {
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Vertex::initVAO() {
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glClearColor(0.576, 0.439, 0.859, 1);
}
