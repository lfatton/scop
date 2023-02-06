#ifndef VECTOR4_HPP
# define VECTOR4_HPP

# include <cmath>

class Vector4 {
private:
public:
    float x, y, z, w;

    explicit Vector4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 1.f);

    Vector4 operator +(Vector4 const &addedVector) const;
    Vector4 operator -(Vector4 const &subtrahendVector) const;
    float operator *(Vector4 const &multiplierVector) const;

    Vector4 operator *(float multiplier) const;
    Vector4& operator =(Vector4 const &vectorToCopy);
    bool operator == (const Vector4& comparedVector) const;
    bool operator != (const Vector4& comparedVector) const;

    [[nodiscard]] float getLength() const;
    void normalise();
    static Vector4 getCrossProduct(Vector4 const &vector1, Vector4 const &vector2);
};

#endif //VECTOR4_HPP
