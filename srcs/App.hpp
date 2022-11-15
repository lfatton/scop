#ifndef APP_HPP
# define APP_HPP

# include <cmath>
# include <algorithm>

# include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

# include "Environment.hpp"
# include "Shader.hpp"
# include "Vertex.hpp"
# include "Vector.hpp"
# include "Matrix.hpp"
# include "Camera.hpp"

static Camera camera;

class App {
private:
    float mSpeed;
    bool mCanChangeSpeed;
    float mSpeedVariation{};

    void renderLoop(GLFWwindow* window, unsigned int shaderProgram, const Vertex& vertex);
    void processInput(GLFWwindow* window);
    static void quit();

public:
    App();
    ~App();
};

#endif //APP_HPP
