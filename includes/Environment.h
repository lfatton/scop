#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <iostream>
# include <c++/9/cstring>
# include <conf.h>

class Environment {
    public:
        void error(char const *error);
        void quit();
        GLFWwindow* init_glfw();
        void init_glad();
};

#endif
