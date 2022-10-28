#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile, fShaderFile;
    std::stringstream vShaderStream, fShaderStream;
    unsigned int vertex, fragment;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();

    createShaderProgram(vShaderCode, fShaderCode);
}

Shader::~Shader() {
    glDeleteShader(this->mShaderProgram);
}

unsigned int Shader::getShaderProgram() const {
    return this->mShaderProgram;
}

void Shader::createShaderProgram(const char* vertexCode, const char* fragmentCode) {
    unsigned int vertex = createShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragment = createShader(GL_FRAGMENT_SHADER, fragmentCode);

    this->mShaderProgram = glCreateProgram();
    glAttachShader(this->mShaderProgram, vertex);
    glAttachShader(this->mShaderProgram, fragment);
    glLinkProgram(this->mShaderProgram);
    checkCompilationErrors(this->mShaderProgram, "PROGRAM");


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

void Shader::checkCompilationErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
            << "\n -- --------------------------------------------------- -- " << std::endl;
            throw std::runtime_error(infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
            << "\n -- --------------------------------------------------- -- " << std::endl;
            throw std::runtime_error(infoLog);
        }
    }
}