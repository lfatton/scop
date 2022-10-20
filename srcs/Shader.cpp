#include "Shader.hpp"

Shader::Shader() {
   createShaderProgram();
}

Shader::~Shader() {
    glDeleteShader(mShaderProgram);
}

unsigned int Shader::getShaderProgram() {
    return mShaderProgram;
}

void Shader::createShaderProgram() {
    unsigned int vertex = createShader(GL_VERTEX_SHADER, VERTEX_SHADER_SRC);
    unsigned int fragment = createShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SRC);

    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, vertex);
    glAttachShader(mShaderProgram, fragment);
    glLinkProgram(mShaderProgram);
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &mSuccess);

    if (!mSuccess) {
        glGetProgramInfoLog(mShaderProgram, 512, nullptr, mInfoLog);
        throw std::runtime_error(mInfoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

unsigned int Shader::createShader(unsigned int type, const char* src) {
    unsigned int shader = glCreateShader(type);

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &mSuccess);

    if (!mSuccess) {
        glGetShaderInfoLog(shader, 512, nullptr, mInfoLog);
        throw std::runtime_error(mInfoLog);
    }

    return shader;
}