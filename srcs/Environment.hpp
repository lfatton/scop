#ifndef ENVIRONMENT_HPP
# define ENVIRONMENT_HPP

# include <iostream>
# include <cstring>

# include "utils.hpp"

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
    void setFramebufferCallback() const;
    void createWindow();
    static void initGlfw();
    static void initGlad();
public:
    GLFWwindow* window = nullptr;

    Environment();
    ~Environment();

    void init();
};


#endif //ENVIRONMENT_HPP
