#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <cmath>
# include <cstring>
# include <iostream>
# include "utils.hpp"
# include "Vector.hpp"

class Matrix {
private:
    float mMatrix[4][4]{};

public:
    Matrix();

    float & operator ()(int row, int column);
    float const& operator ()(int row, int column) const;
    Matrix operator *(Matrix const &multiplierMatrix) const;
    Vector operator *(Vector const &multiplierVector) const;
    [[nodiscard]] float const * getArrayReference() const;

    void getTranslationMatrix(float x, float y, float z);
    void getScalingMatrix(float x, float y, float z);
    void getRotationMatrix(float angle, Vector const &vector);
    void getPerspectiveMatrix(float fov, float ratio, float near, float far);
    void printToConsole();
};

#endif //MATRIX_HPP