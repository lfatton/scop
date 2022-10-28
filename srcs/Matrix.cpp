#include "Matrix.hpp"
#include "Vector.hpp"

#include <cmath>

Matrix::Matrix() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                matrix[i][j] = 1.0f;
            } else {
                matrix[i][j] = 0.0f;
            }
        }
    }
}

float &Matrix::operator()(int row, int column) {
    return matrix[row][column];
}

float const &Matrix::operator()(int row, int column) const {
    return matrix[row][column];
}

Matrix Matrix::operator *(Matrix const &multiplierMatrix) const {
    Matrix result;

    for (int i = 0; i <4; i++) {
        for (int j = 0; j < 4; j++) {
            result(i, j) = this->matrix[i][0] * multiplierMatrix(0, j) +
                           this->matrix[i][1] * multiplierMatrix(1, j) +
                           this->matrix[i][2] * multiplierMatrix(2, j) +
                           this->matrix[i][3] * multiplierMatrix(3, j);
        }
    }

    return result;
}

Vector Matrix::operator *(Vector const &vec) const {
    return Vector(this->matrix[0][0] * vec.x + this->matrix[0][1] * vec.y + this->matrix[0][2] * vec.z + this->matrix[0][3] * vec.w,
                  this->matrix[1][0] * vec.x + this->matrix[1][1] * vec.y + this->matrix[1][2] * vec.z + this->matrix[1][3] * vec.w,
                  this->matrix[2][0] * vec.x + this->matrix[2][1] * vec.y + this->matrix[2][2] * vec.z + this->matrix[2][3] * vec.w,
                  this->matrix[3][0] * vec.x + this->matrix[3][1] * vec.y + this->matrix[3][2] * vec.z + this->matrix[3][3] * vec.w);
}

float const *Matrix::getArrayReference() const
{
    return &this->matrix[0][0];
}

void Matrix::getTranslationMatrix(float x, float y, float z) {
    this->matrix[0][3] = x;
    this->matrix[1][3] = y;
    this->matrix[2][3] = z;
}

void Matrix::getScalingMatrix(float x, float y, float z) {
    this->matrix[0][0] = x;
    this->matrix[1][1] = y;
    this->matrix[2][2] = z;
}

void Matrix::getRotationMatrix(float angleInDegrees, Vector const &axis) {
    float angle = convertToRadians(angleInDegrees);
    float cosA = cosf(angle);
    float sinA = sinf(angle);

    this->matrix[0][0] = cosA + axis.x * axis.x * (1.0f - cosA);
    this->matrix[0][1] = axis.x * axis.y * (1.0f - cosA) - axis.z * sinA;
    this->matrix[0][2] = axis.x * axis.z * (1.0f - cosA) + axis.y * sinA;
    this->matrix[1][0] = axis.x * axis.y * (1.0f - cosA) + axis.z * sinA;
    this->matrix[1][1] = cosA + axis.y * axis.y * (1.0f - cosA);
    this->matrix[1][2] = axis.y * axis.z * (1.0f - cosA) - axis.x * sinA;
    this->matrix[2][0] = axis.x * axis.z * (1.0f - cosA) - axis.y * sinA;
    this->matrix[2][1] = axis.y * axis.z * (1.0f - cosA) + axis.x * sinA;
    this->matrix[2][2] = cosA + axis.z * axis.z * (1.0f - cosA);
}

void Matrix::getPerspectiveMatrix(float fov, float ratio, float near, float far) {
    auto fovTan = tanf(convertToRadians(fov)) * 0.5f;

    this->matrix[0][0] = 1 / (ratio * fovTan);
    this->matrix[1][1] = 1 / fovTan;
    this->matrix[2][2] = (near + far) / (near - far);
    this->matrix[2][3] = 2 * near * far / (near - far);
    this->matrix[3][2] = -1.0f;
//    this->matrix[3][3] = 0.0f;
}

void Matrix::printToConsole() {
    for (auto & i : this->matrix) {
        for (float j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
