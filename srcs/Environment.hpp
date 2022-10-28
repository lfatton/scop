#ifndef ENVIRONMENT_HPP
# define ENVIRONMENT_HPP

# include "glad/glad.h"
# include "GLFW/glfw3.h"
# include <iostream>
# include <cstring>

int const WINDOW_W = 800;
int const WINDOW_H = 600;

# ifdef darwin
const char* const OS = "ios";
# elif unix
const char* const OS = "unix";
# elif _WIN32
const char* const OS = "windows";
# endif

class Environment {
private:
    GLFWwindow* mWindow = nullptr;

    void setFramebufferCallback();
    void createWindow();
    static void initGlfw();
    static void initGlad();

public:
    Environment();
    ~Environment();

    [[nodiscard]] GLFWwindow* getWindow() const;
};


#endif //ENVIRONMENT_HPP
