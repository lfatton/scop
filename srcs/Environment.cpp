
#include "Environment.h"

void Environment::error(char const *error) {
    std::cout << error <<std::endl;
    exit(EXIT_FAILURE);
}

void Environment::quit() {
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

GLFWwindow* Environment::init_glfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    if (strcmp(OS, "windows") == 0 || strcmp(OS, "unix") == 0)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    else
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_W, WINDOW_H, "scop", NULL, NULL);
    if (!window)
        error("Failed to create GLFW window!");

    glfwMakeContextCurrent(window);
    return window;
}

void Environment::init_glad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        error("Failed to initialize GLAD!");
}
