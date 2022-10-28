#ifndef APP_HPP
# define APP_HPP

# include "Environment.hpp"
# include "Shader.hpp"
# include "Vertex.hpp"
# include "Vector.hpp"
# include "Matrix.hpp"

class App {
private:
    double speed;
    bool can_change_speed;
    double speed_variation;

    static void renderLoop(GLFWwindow* window, unsigned int shaderProgram, const Vertex& vertex);
    static void processInput(GLFWwindow* window);
    static void quit();

public:
    App();
    ~App();
};

#endif //APP_HPP
