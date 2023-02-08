#ifndef APP_HPP
# define APP_HPP

# include <cmath>
# include <algorithm>

# include "render/GlfwHandler.hpp"
# include "render/Shader.hpp"
# include "libmath/Matrix.hpp"
# include "render/Camera.hpp"
# include "render/Obj.hpp"

static Camera camera;

class App {
private:
    float mSpeed{};
    bool mCanChangeSpeed{};
    float mSpeedVariation{};
    GlfwHandler glEnvironment;

    void processInput(GLFWwindow* window);
    static void quit();
public:
    Obj obj;

    App();
    ~App();
    void renderLoop();
};

#endif //APP_HPP
