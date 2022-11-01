#ifndef APP_HPP
# define APP_HPP

# include "Environment.hpp"
# include "Shader.hpp"
# include "Vertex.hpp"
# include "Vector.hpp"
# include "Matrix.hpp"

class App {
private:
    double mSpeed;
    bool mCanChangeSpeed;
    double mSpeedVariation;

    void renderLoop(GLFWwindow* window, unsigned int shaderProgram, const Vertex& vertex);
    void processInput(GLFWwindow* window);
    static void quit();

public:
    App();
    ~App();
};

#endif //APP_HPP
