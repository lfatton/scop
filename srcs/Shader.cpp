#include "Shader.hpp"

Shader::Shader() {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile, fShaderFile;
    std::stringstream vShaderStream, fShaderStream;
    unsigned int vertex, fragment;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(VERT_PATH);
        fShaderFile.open(FRAG_PATH);

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure &e) {
        scopError("error: cannot read shader file", e.what());
    }

    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();

    createShaderProgram(vShaderCode, fShaderCode);
}

Shader::~Shader() {
    glDeleteShader(this->shaderProgram);
}

void Shader::createShaderProgram(const char* vertexCode, const char* fragmentCode) {
    unsigned int vertex = createShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragment = createShader(GL_FRAGMENT_SHADER, fragmentCode);

    this->shaderProgram = glCreateProgram();
    glAttachShader(this->shaderProgram, vertex);
    glAttachShader(this->shaderProgram, fragment);
    glLinkProgram(this->shaderProgram);
    checkCompilationErrors(this->shaderProgram, "PROGRAM");


    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

unsigned int Shader::createShader(unsigned int type, const char* src) {
    unsigned int shader = glCreateShader(type);

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    if (type == GL_VERTEX_SHADER)
        checkCompilationErrors(shader, "VERTEX");
    else
        checkCompilationErrors(shader, "FRAGMENT");

    return shader;
}

void Shader::checkCompilationErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            scopError("error: cannot compile shader of type: " + type, infoLog);
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            scopError("error: cannot link shader program of type: " + type, infoLog);
        }
    }
}