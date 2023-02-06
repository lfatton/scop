#ifndef APP_HPP
# define APP_HPP

# include <cmath>
# include <algorithm>

# include "Environment.hpp"
# include "Shader.hpp"
# include "Vector4.hpp"
# include "Matrix.hpp"
# include "Camera.hpp"
# include "Obj.hpp"

static Camera camera;

class App {
private:
    float mSpeed{};
    bool mCanChangeSpeed{};
    float mSpeedVariation{};
    Environment glEnvironment;

    void processInput(GLFWwindow* window);
    static void quit();
public:
    Obj obj;

    App();
    ~App();
    void renderLoop();
};

#endif //APP_HPP
