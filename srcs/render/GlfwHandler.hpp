#ifndef GLFW_HANDLER_HPP
# define GLFW_HANDLER_HPP

# include <iostream>
# include <cstring>

# include "../utils.hpp"

int const WINDOW_W = 1920;
int const WINDOW_H = 1080;

# ifdef darwin
const char* const OS = "ios";
# elif unix
const char* const OS = "unix";
# elif _WIN32
const char* const OS = "windows";
# endif

class GlfwHandler {
private:
    void setFramebufferCallback() const;
    void createWindow();
    static void initGlfw();
    static void initGlad();
public:
    GLFWwindow* window = nullptr;

    GlfwHandler();
    ~GlfwHandler();

    void init();
};


#endif //GLFW_HANDLER_HPP
