#include <iostream>
#include "Camera.hpp"

Camera::Camera(Vector &givenPosition, Vector &givenTarget) {
    position = givenPosition;
    target = givenTarget;

    zAxis = position + target;
    zAxis.getUnitVector();

    xAxis = Vector::getCrossProduct(Vector(0.0f, 1.0f, 0.0f), zAxis);
    xAxis.getUnitVector();

    yAxis = Vector::getCrossProduct(zAxis, xAxis);
}

Camera& Camera::operator= (const Camera &cameraToCopy) = default;
