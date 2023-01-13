#ifndef APP_HPP
# define APP_HPP

# include <cmath>
# include <algorithm>

# include "Environment.hpp"
# include "Shader.hpp"
# include "Vertex.hpp"
# include "Vector.hpp"
# include "Matrix.hpp"
# include "Camera.hpp"
# include "Parser.hpp"

static Camera camera;

class App {
private:
    float mSpeed{};
    bool mCanChangeSpeed{};
    float mSpeedVariation{};

    void processInput(GLFWwindow* window);
    static void quit();
public:
    Environment glEnvironment;
    Shader shader;
    Parser parser;

    App();
    ~App();
    void renderLoop();
};

#endif //APP_HPP
