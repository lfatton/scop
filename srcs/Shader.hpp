#ifndef SHADER_HPP
# define SHADER_HPP

# include "glad/glad.h"
# include "GLFW/glfw3.h"
# include <iostream>
# include <cstring>
# include <fstream>
# include <sstream>

# include "utils.hpp"

const char* VERT_PATH = "../shaders/shader.vert";
const char* FRAG_PATH = "../shaders/shader.frag";

class Shader {
private:
    void createShaderProgram(const char* vertex, const char* fragment);
    static unsigned int createShader(unsigned int type, const char* src);
    static void checkCompilationErrors(unsigned int shader, std::string type);

public:
    unsigned int shaderProgram{};

    Shader();
    ~Shader();
};


# endif //SHADER_HPP
