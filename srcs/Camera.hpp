#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "Vector.hpp"
# include "Matrix.hpp"
# include "Environment.hpp"

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
float const SENSITIVITY = 0.1f;

static Vector initialPosition(0.f, 0.f, 3.f);
static Vector initialTarget(0.f, 0.f, -1.f);

class Camera {
private:
    bool mFirstTime = true;
    float mLastX = (float)WINDOW_W / 2;
    float mLastY = (float)WINDOW_H / 2;
public:
    float zoomValue = FOV;
    float speedValue = SPEED;
    float yaw = YAW;
    float pitch = PITCH;
    Vector position{}, target{}, xAxis{}, yAxis{}, zAxis{};

    explicit Camera(Vector &givenPosition = initialPosition, Vector &givenTarget = initialTarget, float givenZoom = FOV);

    Camera& operator =(Camera const &cameraToCopy);

    void update();
    void move(Direction direction, float deltaTime);
    void rotate(float xPos, float yPos);
    void zoom(float yOffset);
};

#endif //CAMERA_HPP
