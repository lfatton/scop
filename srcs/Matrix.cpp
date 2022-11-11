#include "Matrix.hpp"
#include "Vector.hpp"

Matrix::Matrix() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                mMatrix[i][j] = 1.f;
            } else {
                mMatrix[i][j] = 0.f;
            }
        }
    }
}

float &Matrix::operator ()(int row, int column) {
    return mMatrix[row][column];
}

float const &Matrix::operator ()(int row, int column) const {
    return mMatrix[row][column];
}

Matrix Matrix::operator *(Matrix const &multiplierMatrix) const {
    Matrix result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result(i, j) = this->mMatrix[i][0] * multiplierMatrix(0, j)
                    + this->mMatrix[i][1] * multiplierMatrix(1, j)
                    + this->mMatrix[i][2] * multiplierMatrix(2, j)
                    + this->mMatrix[i][3] * multiplierMatrix(3, j);
        }
    }

    return result;
}

Vector Matrix::operator *(Vector const &multiplierVector) const {
    return Vector(this->mMatrix[0][0] * multiplierVector.x + this->mMatrix[0][1] * multiplierVector.y
    + this->mMatrix[0][2] * multiplierVector.z + this->mMatrix[0][3] * multiplierVector.w,
    this->mMatrix[1][0] * multiplierVector.x + this->mMatrix[1][1] * multiplierVector.y
    + this->mMatrix[1][2] * multiplierVector.z + this->mMatrix[1][3] * multiplierVector.w,
    this->mMatrix[2][0] * multiplierVector.x + this->mMatrix[2][1] * multiplierVector.y
    + this->mMatrix[2][2] * multiplierVector.z + this->mMatrix[2][3] * multiplierVector.w,
    this->mMatrix[3][0] * multiplierVector.x + this->mMatrix[3][1] * multiplierVector.y
    + this->mMatrix[3][2] * multiplierVector.z + this->mMatrix[3][3] * multiplierVector.w);
}

Matrix& Matrix::operator =(const Matrix &matrixToCopy) = default;

float const *Matrix::getArrayReference() const {
    return &this->mMatrix[0][0];
}

void Matrix::translate(float x, float y, float z) {
    this->mMatrix[0][3] = x;
    this->mMatrix[1][3] = y;
    this->mMatrix[2][3] = z;
}

void Matrix::scale(float x, float y, float z) {
    this->mMatrix[0][0] = x;
    this->mMatrix[1][1] = y;
    this->mMatrix[2][2] = z;
}

void Matrix::rotate(float angleInDegrees, Vector &axis) {
    axis.normalise();

    float angle = convertToRadians(angleInDegrees);
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);

    this->mMatrix[0][0] = cosAngle + axis.x * axis.x * (1.f - cosAngle);
    this->mMatrix[0][1] = axis.x * axis.y * (1.f - cosAngle) - axis.z * sinAngle;
    this->mMatrix[0][2] = axis.x * axis.z * (1.f - cosAngle) + axis.y * sinAngle;
    this->mMatrix[1][0] = axis.y * axis.x * (1.f - cosAngle) + axis.z * sinAngle;
    this->mMatrix[1][1] = cosAngle + axis.y * axis.y * (1.f - cosAngle);
    this->mMatrix[1][2] = axis.y * axis.z * (1.f - cosAngle) - (axis.x * sinAngle);
    this->mMatrix[2][0] = axis.z * axis.x * (1.f - cosAngle) - axis.y * sinAngle;
    this->mMatrix[2][1] = axis.z * axis.y * (1.f - cosAngle) + (axis.x * sinAngle);
    this->mMatrix[2][2] = cosAngle + axis.z * axis.z * (1.f - cosAngle);
}

Matrix Matrix::getPerspectiveMatrix(float fov, float ratio, float near, float far) {
    Matrix perspective;
    auto fovTan = tanf(convertToRadians(fov) * 0.5f);

    perspective(0, 0) = 1.f / (ratio * fovTan);
    perspective(1, 1) = 1.f / fovTan;
    perspective(2, 2) = (near + far) / (near - far);
    perspective(2, 3) = 2.f * near * far / (near - far);
    perspective(3, 2) = -1.f;
    perspective(3, 3) = 0.f;

    return perspective;
}

Matrix Matrix::getLookAtMatrix(Vector &xAxis, Vector &yAxis, Vector &zAxis, Vector &position) {
    Matrix lookAt;

    lookAt(0, 0) = xAxis.x;
    lookAt(0, 1) = xAxis.y;
    lookAt(0, 2) = xAxis.z;
    lookAt(1, 0) = yAxis.x;
    lookAt(1, 1) = yAxis.y;
    lookAt(1, 2) = yAxis.z;
    lookAt(2, 0) = zAxis.x;
    lookAt(2, 1) = zAxis.y;
    lookAt(2, 2) = zAxis.z;

    Matrix positionMatrix;
    positionMatrix.translate(-position.x, -position.y, -position.z);

    lookAt = positionMatrix * lookAt;

    return lookAt;
}

void Matrix::printToConsole() {
    for (auto &i: this->mMatrix) {
        for (float j: i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
