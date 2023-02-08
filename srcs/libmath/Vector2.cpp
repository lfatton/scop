#include "Vector2.hpp"

Vector2::Vector2(float x, float y): x(x), y(y){}

Vector2 Vector2::operator +(Vector2 const &addedVector) const {
    return Vector2(this->x + addedVector.x, this->y + addedVector.y);
}

Vector2 Vector2::operator -(Vector2 const &subtrahendVector) const {
    return Vector2(this->x - subtrahendVector.x, this->y - subtrahendVector.y);
}

float Vector2::operator *(Vector2 const &multiplierVector) const {
    return acosf(this->x * multiplierVector.x + this->y * multiplierVector.y);
}

Vector2 Vector2::operator *(const float multiplier) const {
    return Vector2(this->x * multiplier, this->y * multiplier);
}

Vector2& Vector2::operator =(const Vector2 &vectorToCopy) = default;

bool Vector2::operator ==(const Vector2 &comparedVector) const {
    if (this->x == comparedVector.x
        && this->y == comparedVector.y)
        return true;

    return false;
}

bool Vector2::operator !=(const Vector2 &comparedVector) const {
    if (this->x != comparedVector.x
        || this->y != comparedVector.y)
        return true;

    return false;
}

float Vector2::getLength() const {
    return sqrtf(this->x * this->x + this->y * this->y);
}

void Vector2::normalise() {
    float length = this->getLength();

    if (length == 0.f)
        return ;

    this->x = this->x / length;
    this->y = this->y / length;
}