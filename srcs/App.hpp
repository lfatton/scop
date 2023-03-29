#ifndef APP_HPP
# define APP_HPP

# include <cmath>
# include <algorithm>

# include "render/GlfwHandler.hpp"
# include "render/Shader.hpp"
# include "libmath/Matrix.hpp"
# include "render/Camera.hpp"
# include "render/Obj.hpp"
# include "render/LoaderBMP.hpp"

static Camera camera;
static unsigned int textIndex{};
static bool flatMode{}, colourMode{}, greyscaleMode{};
static GLenum currentGlMode{};

class App {
private:
    float mSpeed{}, mColourSpeed{}, mColourSpeedVariation{}, mModelRotationalAngle{};
    GlfwHandler glEnvironment{};
    GLuint mTexture[3]{};
    bool mCanChangeColourSpeed{};
    Matrix mModel{};
    Vector3 mModelRotationalAxis{};

    void processInput(GLFWwindow* window);
    void setCallbacks() const;
    static void printHelpToConsole();
    static void quit();
public:
    Obj obj;

    App();
    ~App();
    void renderLoop();
};

#endif //APP_HPP
