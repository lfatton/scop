#ifndef SHADER_HPP
# define SHADER_HPP

# include <iostream>
# include <cstring>
# include <fstream>
# include <sstream>

# include "../utils.hpp"


class Shader {
private:
    const char* VERT_PATH = "../assets/shaders/shader.vert";
    const char* FRAG_PATH = "../assets/shaders/shader.frag";

    void createShaderProgram(const char* vertex, const char* fragment);
    static unsigned int createShader(unsigned int type, const char* src);
    static void checkCompilationErrors(unsigned int shader, const std::string& type);
public:
    unsigned int shaderProgram{};

    Shader();
    ~Shader();
};


# endif //SHADER_HPP
