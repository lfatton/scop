#include "Camera.hpp"

Camera::Camera(Vector &givenPosition, Vector &givenTarget) {
    position = givenPosition;
    target = givenTarget;

    zAxis = position + target;
    zAxis.normalise();

    xAxis = Vector::getCrossProduct(Vector(0.f, 1.f, 0.f), zAxis);
    xAxis.normalise();

    yAxis = Vector::getCrossProduct(zAxis, xAxis);
}

Camera& Camera::operator= (const Camera &cameraToCopy) = default;
