#ifndef VERTEX_HPP
# define VERTEX_HPP

# include "glad/glad.h"
# include "GLFW/glfw3.h"

const float VERTICES[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
};
class Vertex {
private:
    unsigned int mVBO, mVAO;

    void initObjects();

public:
    Vertex();
    ~Vertex();

    unsigned int getVAO();
};


#endif //VERTEX_HPP
