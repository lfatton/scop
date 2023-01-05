#include "Camera.hpp"

Camera::Camera(Vector &givenPosition, Vector &givenTarget, float givenZoom) {
    zoomValue = givenZoom;
    position = givenPosition;
    target = givenTarget;

    zAxis = position + target;
    zAxis.normalise();

    xAxis = Vector::getCrossProduct(Vector(0.f, 1.f, 0.f), zAxis);
    xAxis.normalise();

    yAxis = Vector::getCrossProduct(zAxis, xAxis);
}

Camera& Camera::operator= (const Camera &cameraToCopy) = default;

void Camera::update() {
    Camera updatedCam(this->position, this->target, this->zoomValue);
    *this = updatedCam;
}

void Camera::move(Direction direction, float deltaTime) {
    float velocity = this->speedValue * deltaTime;
    velocity = 0.05f;
    Vector right = Vector::getCrossProduct(this->target, this->yAxis);
    right.normalise();

    if (direction == FORWARD)
        this->position = this->position + this->target * velocity;
    if (direction == BACKWARD)
        this->position = this->position - this->target * velocity;
    if (direction == LEFT)
        this->position = this->position - right * velocity;
    if (direction == RIGHT)
        this->position = this->position + right * velocity;
    this->update();
}

void Camera::rotate(float xPos, float yPos) {
    float xOffset = xPos - this->mLastX;
    float yOffset = this->mLastY - yPos;
    this->mLastX = xPos;
    this->mLastY = yPos;

    xOffset *= SENSITIVITY;
    yOffset *= SENSITIVITY;

    this->yaw   += xOffset;
    this->pitch += yOffset;

    if (this->pitch > PITCH_LIMIT)
        this->pitch = PITCH_LIMIT;
    if (this->pitch < -PITCH_LIMIT)
        this->pitch = -PITCH_LIMIT;

    Vector direction;
    direction.x = cosf(convertToRadians(this->yaw)) * cosf(convertToRadians(this->pitch));
    direction.y = sinf(convertToRadians(this->pitch));
    direction.z = sinf(convertToRadians(this->yaw)) * cosf(convertToRadians(this->pitch));
    direction.normalise();
    this->target = direction;
    this->update();
}

void Camera::zoom(float yOffset) {
    this->zoomValue -= yOffset;

    if (this->zoomValue < 1.f)
        this->zoomValue = 1.f;
    if (this->zoomValue > FOV)
        this->zoomValue = FOV;
}
