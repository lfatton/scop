#include "Vector3.hpp"

Vector3::Vector3(float x, float y, float z): x(x), y(y), z(z) {}

Vector3 Vector3::operator +(Vector3 const &addedVector) const {
    return Vector3(this->x + addedVector.x, this->y + addedVector.y, this->z + addedVector.z);
}

Vector3 Vector3::operator -(Vector3 const &subtrahendVector) const {
    return Vector3(this->x - subtrahendVector.x, this->y - subtrahendVector.y, this->z - subtrahendVector.z);
}

float Vector3::operator *(Vector3 const &multiplierVector) const {
    return acosf(this->x * multiplierVector.x + this->y * multiplierVector.y + this->z * multiplierVector.z);
}

Vector3 Vector3::operator *(const float multiplier) const {
    return Vector3(this->x * multiplier, this->y * multiplier, this->z * multiplier);
}

Vector3& Vector3::operator =(const Vector3 &vectorToCopy) = default;

bool Vector3::operator ==(const Vector3 &comparedVector) const {
    if (this->x == comparedVector.x
        && this->y == comparedVector.y
        && this->z == comparedVector.z)
        return true;

    return false;
}

bool Vector3::operator !=(const Vector3 &comparedVector) const {
    if (this->x != comparedVector.x
        || this->y != comparedVector.y
        || this->z != comparedVector.z)
        return true;

    return false;
}

float Vector3::getLength() const {
    return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

void Vector3::normalise() {
    float length = this->getLength();

    if (length == 0.f)
        return ;

    this->x = this->x / length;
    this->y = this->y / length;
    this->z = this->z / length;
}

Vector3 Vector3::getCrossProduct(Vector3 const &vector1, Vector3 const &vector2) {
    return Vector3(vector1.y * vector2.z - vector1.z * vector2.y,
                   vector1.z * vector2.x - vector1.x * vector2.z,
                   vector1.x * vector2.y - vector1.y * vector2.x);
}
