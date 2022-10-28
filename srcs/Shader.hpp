#ifndef SHADER_HPP
# define SHADER_HPP

# include "glad/glad.h"
# include "GLFW/glfw3.h"
# include <iostream>
# include <cstring>
# include <fstream>
# include <sstream>

class Shader {
private:
    unsigned int mShaderProgram{};

    void createShaderProgram(const char* vertex, const char* fragment);
    static unsigned int createShader(unsigned int type, const char* src);
    static void checkCompilationErrors(unsigned int shader, std::string type);
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    [[nodiscard]] unsigned int getShaderProgram() const;
};


# endif //SHADER_HPP
