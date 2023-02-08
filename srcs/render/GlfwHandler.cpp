#include "GlfwHandler.hpp"

GlfwHandler::GlfwHandler() = default;

GlfwHandler::~GlfwHandler() {
    glfwDestroyWindow(this->window);
}

void GlfwHandler::initGlfw() {
    if (!glfwInit())
        scopError("error: failed to initialize GLFW!", "");
}

void GlfwHandler::initGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        scopError("error: failed to initialize GLAD!", "");
}

void GlfwHandler::createWindow() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    if (strcmp(OS, "windows") == 0 || strcmp(OS, "unix") == 0)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    else
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this->window = glfwCreateWindow(WINDOW_W, WINDOW_H, "scop", nullptr, nullptr);

    if (!this->window) {
        const char *description;
        int code = glfwGetError(&description);

        if (description) {
            glfwTerminate();
            scopError("error: failed to create GLFW window",description);
        }
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GlfwHandler::setFramebufferCallback() const {
    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow* callbackWindow, int width, int height) {
        glViewport(0, 0, width, height);
    });
}

void GlfwHandler::init() {
    GlfwHandler::initGlfw();
    this->createWindow();
    GlfwHandler::initGlad();
    this->setFramebufferCallback();
}