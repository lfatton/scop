#include "Camera.hpp"

Camera::Camera(Vector3 &givenPosition, Vector3 &givenTarget, float givenZoom) {
    zoomValue = givenZoom;
    position = givenPosition;
    target = givenTarget;

    zAxis = position - target;
    zAxis.normalise();

    xAxis = Vector3::getCrossProduct(Vector3(0.f, 1.f, 0.f), zAxis);
    xAxis.normalise();

    yAxis = Vector3::getCrossProduct(zAxis, xAxis);
}

Camera& Camera::operator= (const Camera &cameraToCopy) = default;

void Camera::update() {
    Camera updatedCam(this->position, this->target, this->zoomValue);
    *this = updatedCam;
}

void Camera::move(Direction direction, float deltaTime) {
    float velocity = this->speedValue * deltaTime;
    velocity = 0.001f;
    Vector3 right = Vector3::getCrossProduct(this->target, this->yAxis);
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

    Vector3 direction(cosf(convertToRadians(this->yaw)) * cosf(convertToRadians(this->pitch)),
                      sinf(convertToRadians(this->pitch)),
                      sinf(convertToRadians(this->yaw)) * cosf(convertToRadians(this->pitch)));
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
