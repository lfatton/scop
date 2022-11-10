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
    Matrix& operator =(Matrix const &matrixToCopy);

    [[nodiscard]] float const * getArrayReference() const;
    void getTranslationMatrix(float x, float y, float z);
    void getScalingMatrix(float x, float y, float z);
    static Matrix getRotationMatrix(float angle, Vector const &vector);
    static Matrix getPerspectiveMatrix(float fov, float ratio, float near, float far);
    static Matrix getLookAtMatrix(Vector &xAxis, Vector &yAxis, Vector &zAxis, Vector &position);
    void printToConsole();
};

#endif //MATRIX_HPP