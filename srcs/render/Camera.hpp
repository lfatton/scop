#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "../libmath/Matrix.hpp"
# include "GlfwHandler.hpp"

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

float const FOV = 45.f;
float const SPEED = 2.5f;
float const YAW = -90.f;
float const PITCH = 0.f;
float const PITCH_LIMIT = 89.f;
float const SENSITIVITY = 0.05f;

static Vector3 initialPosition(0.f, 0.f, 5.f);
static Vector3 initialTarget(0.f, 0.f, -1.f);

class Camera {
private:
    float mLastX = (float)WINDOW_W / 2;
    float mLastY = (float)WINDOW_H / 2;
public:
    float zoomValue = FOV;
    float speedValue = SPEED;
    float yaw = YAW;
    float pitch = PITCH;
    Vector3 position{}, target{}, xAxis{}, yAxis{}, zAxis{};

    explicit Camera(Vector3 &givenPosition = initialPosition, Vector3 &givenTarget = initialTarget, float givenZoom = FOV);

    Camera& operator =(Camera const &cameraToCopy);

    void update();
    void move(Direction direction, float deltaTime);
    void rotate(float xPos, float yPos);
    void zoom(float yOffset);
};

#endif //CAMERA_HPP
