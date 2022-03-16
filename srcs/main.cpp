#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <conf.h>

void error_scop(char *error)
{
    std::cout << error <<std::endl;
    exit(EXIT_FAILURE);
}


GLFWwindow* init_glfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    if (OS == "unix" || "windows")
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    else
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_W, WINDOW_H, "scop", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        error_scop("Failed to create GLFW window!");
    }

    glfwMakeContextCurrent(window);
    return window;
}

void init_glad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        error_scop("Failed to initialize GLAD!");
}

int main()
{
    init_glfw();
    init_glad();

    return 0;
}