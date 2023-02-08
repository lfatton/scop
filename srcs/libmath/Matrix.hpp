#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <cmath>
# include <cstring>
# include <iostream>
# include "../utils.hpp"
# include "Vector4.hpp"

class Matrix {
private:
    float mMatrix[4][4]{};

public:
    Matrix();

    float & operator ()(unsigned int row, unsigned int column);
    float const& operator ()(unsigned int row, unsigned int column) const;
    Matrix operator *(Matrix const &multiplierMatrix) const;
    Vector4 operator *(Vector4 const &multiplierVector) const;
    Matrix& operator =(Matrix const &matrixToCopy);

    [[nodiscard]] float const * getArrayReference() const;
    void translate(float x, float y, float z);
    void scale(float x, float y, float z);
    void rotate(float angle, Vector3 &vector);

    static Matrix getPerspectiveMatrix(float fov, float ratio, float near, float far);
    static Matrix getLookAtMatrix(Vector3 &xAxis, Vector3 &yAxis, Vector3 &zAxis, Vector3 &position);
    void printToConsole();
};

#endif //MATRIX_HPP