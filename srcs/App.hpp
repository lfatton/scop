#ifndef APP_HPP
# define APP_HPP

# include "Environment.hpp"
# include "Shader.hpp"
# include "Vertex.hpp"

class App {
private:
    void renderLoop(GLFWwindow* window, unsigned int shaderProgram, unsigned int VAO);
    void processInput(GLFWwindow* window);
    void quit();
    double speed;
    bool can_change_speed;
    double speed_variation;

public:
    App();
    ~App();
};

#endif //APP_HPP
