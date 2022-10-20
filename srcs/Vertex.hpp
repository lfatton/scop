#ifndef VERTEX_HPP
# define VERTEX_HPP

# include "glad/glad.h"
# include "GLFW/glfw3.h"

float const VERTICES[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
};

class Vertex {
private:
    unsigned int mVBO, mVAO;

    void initVBO();
    void initVAO();

public:
    Vertex();
    ~Vertex();

    unsigned int getVAO();
};


#endif //VERTEX_HPP
