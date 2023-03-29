#include "Vector4.hpp"

Vector4::Vector4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}

Vector4::Vector4(Vector3 vector, float w) {
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;
    this->w = w;
}

Vector4 Vector4::operator +(Vector4 const &addedVector) const {
    return Vector4(this->x + addedVector.x, this->y + addedVector.y,
                   this->z + addedVector.z, this->w + addedVector.w);
}

Vector4 Vector4::operator -(Vector4 const &subtrahendVector) const {
    return Vector4(this->x - subtrahendVector.x, this->y - subtrahendVector.y,
                   this->z - subtrahendVector.z, this->w - subtrahendVector.w);
}

float Vector4::operator *(Vector4 const &multiplierVector) const {
    return acosf(this->x * multiplierVector.x + this->y * multiplierVector.y +
    this->z * multiplierVector.z + this->w * multiplierVector.w);
}

Vector4 Vector4::operator *(const float multiplier) const {
    return Vector4(this->x * multiplier, this->y * multiplier, this->z * multiplier, this->w * multiplier);
}

Vector4 Vector4::operator /(const float divider) const {
    return Vector4(this->x / divider, this->y / divider, this->z / divider, this->w / divider);
}

Vector4& Vector4::operator =(const Vector4 &vectorToCopy) = default;

bool Vector4::operator ==(const Vector4 &comparedVector) const {
    if (this->x == comparedVector.x
        && this->y == comparedVector.y
            && this->z == comparedVector.z
                && this->w == comparedVector.w)
        return true;

    return false;
}

bool Vector4::operator !=(const Vector4 &comparedVector) const {
    if (this->x != comparedVector.x
        || this->y != comparedVector.y
           || this->z != comparedVector.z
              || this->w != comparedVector.w)
        return true;

    return false;
}

float Vector4::getLength() const {
    return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

void Vector4::normalise() {
    float length = this->getLength();

    if (length == 0.f)
        return ;

    this->x = this->x / length;
    this->y = this->y / length;
    this->z = this->z / length;
    this->w = this->w / length;
}

Vector4 Vector4::getCrossProduct(Vector4 const &vector1, Vector4 const &vector2) {
    return Vector4(vector1.y * vector2.z - vector1.z * vector2.y,
                  vector1.z * vector2.x - vector1.x * vector2.z,
                  vector1.x * vector2.y - vector1.y * vector2.x,
                  vector1.w * vector2.w);
}
