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

void Vector::getCrossProduct(Vector const &secondVector) {
    Vector result = Vector(this->y * secondVector.z - this->z * secondVector.y,
                           this->z * secondVector.x - this->x * secondVector.z,
                           this->x * secondVector.y - this->y * secondVector.x);

    this->x = result.x;
    this->y = result.y;
    this->z = result.z;
}