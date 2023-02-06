#ifndef VECTOR2_HPP
# define VECTOR2_HPP

# include <cmath>

class Vector2 {
private:
public:
    float x, y;

    explicit Vector2(float x = 0.f, float y = 0.f);

    Vector2 operator +(Vector2 const &addedVector) const;
    Vector2 operator -(Vector2 const &subtrahendVector) const;
    float operator *(Vector2 const &multiplierVector) const;

    Vector2 operator *(float multiplier) const;
    Vector2& operator =(Vector2 const &vectorToCopy);
    bool operator == (const Vector2& comparedVector) const;
    bool operator != (const Vector2& comparedVector) const;

    [[nodiscard]] float getLength() const;
    void normalise();
};


#endif //VECTOR2_HPP
