#include "Matrix.hpp"
#include "Vector.hpp"

Matrix::Matrix() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                mMatrix[i][j] = 1.0f;
            } else {
                mMatrix[i][j] = 0.0f;
            }
        }
    }
}

float &Matrix::operator()(int row, int column) {
    return mMatrix[row][column];
}

float const &Matrix::operator()(int row, int column) const {
    return mMatrix[row][column];
}

Matrix Matrix::operator*(Matrix const &multiplierMatrix) const {
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

Vector Matrix::operator*(Vector const &multiplierVector) const {
    return Vector(this->mMatrix[0][0] * multiplierVector.x + this->mMatrix[0][1] * multiplierVector.y
    + this->mMatrix[0][2] * multiplierVector.z + this->mMatrix[0][3] * multiplierVector.w,
    this->mMatrix[1][0] * multiplierVector.x + this->mMatrix[1][1] * multiplierVector.y
    + this->mMatrix[1][2] * multiplierVector.z + this->mMatrix[1][3] * multiplierVector.w,
    this->mMatrix[2][0] * multiplierVector.x + this->mMatrix[2][1] * multiplierVector.y
    + this->mMatrix[2][2] * multiplierVector.z + this->mMatrix[2][3] * multiplierVector.w,
    this->mMatrix[3][0] * multiplierVector.x + this->mMatrix[3][1] * multiplierVector.y
    + this->mMatrix[3][2] * multiplierVector.z + this->mMatrix[3][3] * multiplierVector.w);
}

float const *Matrix::getArrayReference() const {
    return &this->mMatrix[0][0];
}

void Matrix::getTranslationMatrix(float x, float y, float z) {
    this->mMatrix[0][3] = x;
    this->mMatrix[1][3] = y;
    this->mMatrix[2][3] = z;
}

void Matrix::getScalingMatrix(float x, float y, float z) {
    this->mMatrix[0][0] = x;
    this->mMatrix[1][1] = y;
    this->mMatrix[2][2] = z;
}

void Matrix::getRotationMatrix(float angleInDegrees, Vector const &axis) {
    float angle = convertToRadians(angleInDegrees);
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);

    this->mMatrix[0][0] = cosAngle + axis.x * axis.x * (1.0f - cosAngle);
    this->mMatrix[0][1] = axis.x * axis.y * (1.0f - cosAngle) - axis.z * sinAngle;
    this->mMatrix[0][2] = axis.x * axis.z * (1.0f - cosAngle) + axis.y * sinAngle;
    this->mMatrix[1][0] = axis.x * axis.y * (1.0f - cosAngle) + axis.z * sinAngle;
    this->mMatrix[1][1] = cosAngle + axis.y * axis.y * (1.0f - cosAngle);
    this->mMatrix[1][2] = axis.y * axis.z * (1.0f - cosAngle) - axis.x * sinAngle;
    this->mMatrix[2][0] = axis.x * axis.z * (1.0f - cosAngle) - axis.y * sinAngle;
    this->mMatrix[2][1] = axis.y * axis.z * (1.0f - cosAngle) + axis.x * sinAngle;
    this->mMatrix[2][2] = cosAngle + axis.z * axis.z * (1.0f - cosAngle);
}

void Matrix::getPerspectiveMatrix(float fov, float ratio, float near, float far) {
    auto fovTan = tanf(convertToRadians(fov)) * 0.5f;

    this->mMatrix[0][0] = 1 / (ratio * fovTan);
    this->mMatrix[1][1] = 1 / fovTan;
    this->mMatrix[2][2] = (near + far) / (near - far);
    this->mMatrix[2][3] = 2 * near * far / (near - far);
    this->mMatrix[3][2] = -1.0f;
//    this->matrix[3][3] = 0.0f;
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
