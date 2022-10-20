#ifndef SHADER_HPP
# define SHADER_HPP

# include "glad/glad.h"
# include "GLFW/glfw3.h"
# include <iostream>
# include <cstring>

const char* const VERTEX_SHADER_SRC = "#version 460 core\n"
                                      "layout (location = 0) in vec3 aPos;\n"
                                      "void main()\n"
                                      "{\n"
                                      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                      "}\0";

const char* const FRAGMENT_SHADER_SRC = "#version 460 core\n"
                                        "out vec4 FragColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 0.3f);\n"
                                        "}\n\0";

class Shader {
private:
    int  mSuccess;
    char mInfoLog[512];
    unsigned int mShaderProgram;

    void createShaderProgram();
    unsigned int createShader(unsigned int type, const char* src);
public:
    Shader();
    ~Shader();

    unsigned int getShaderProgram();
};


# endif SHADER_HPP
