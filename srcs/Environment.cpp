#include "Environment.hpp"

Environment::Environment() {
    initGlfw();
    createWindow();
    initGlad();
    setFramebufferCallback();
}

Environment::~Environment() {
    glfwDestroyWindow(mWindow);
}

GLFWwindow *Environment::getWindow() {
    return mWindow;
}

void Environment::initGlfw() {
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW!");
}

void Environment::initGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD!");
}

void Environment::createWindow() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    if (strcmp(OS, "windows") == 0 || strcmp(OS, "unix") == 0)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    else
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mWindow = glfwCreateWindow(WINDOW_W, WINDOW_H, "scop", NULL, NULL);

    if (!mWindow) {
        const char *description;
        int code = glfwGetError(&description);

        if (description) {
            glfwTerminate();
            throw std::runtime_error("\nCODE: " + std::to_string(code) + "\n" + description);
        }
    }
    glfwMakeContextCurrent(mWindow);
}

void Environment::setFramebufferCallback() {
    glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, WINDOW_W, WINDOW_H);
    });
}