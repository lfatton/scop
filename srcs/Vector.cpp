#include <iostream>
#include "Vector.hpp"

Vector::Vector(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}

Vector Vector::operator +(Vector const &addedVector) const
{
    return Vector(this->x + addedVector.x, this->y + addedVector.y, this->z + addedVector.z);
}

Vector Vector::operator -(Vector const &subtrahendVector) const
{
    return Vector(this->x - subtrahendVector.x, this->y - subtrahendVector.y, this->z - subtrahendVector.z);
}

float Vector::operator *(Vector const &multiplierVector) const
{
    return acosf(this->x * multiplierVector.x + this->y * multiplierVector.y + this->z * multiplierVector.z);
}

Vector Vector::operator *(const float multiplier) const {
    return Vector(x * multiplier, y * multiplier, z * multiplier);
}

Vector& Vector::operator =(const Vector &vectorToCopy) = default;

float Vector::getLength() const {
    return fsqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

void Vector::getUnitVector() {
    float length = this->getLength();

    if (length == 0.0f)
        return ;

    this->x = this->x / length;
    this->y = this->y / length;
    this->z = this->z / length;
}

Vector Vector::getCrossProduct(Vector const &vector1, Vector const &vector2) {
    return Vector(vector1.y * vector2.z - vector1.z * vector2.y,
                  vector1.z * vector2.x - vector1.x * vector2.z,
                  vector1.x * vector2.y - vector1.y * vector2.x);

}