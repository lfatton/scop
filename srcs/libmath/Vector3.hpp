#ifndef VECTOR3_HPP
# define VECTOR3_HPP

# include <cmath>

class Vector3 {
private:
public:
    float x, y, z;

    explicit Vector3(float x = 0.f, float y = 0.f, float z = 0.f);

    Vector3 operator +(Vector3 const &addedVector) const;
    Vector3 operator -(Vector3 const &subtrahendVector) const;
    float operator *(Vector3 const &multiplierVector) const;

    Vector3 operator *(float multiplier) const;
    Vector3 operator /(float multiplier) const;
    Vector3& operator =(Vector3 const &vectorToCopy);
    bool operator == (const Vector3& comparedVector) const;
    bool operator != (const Vector3& comparedVector) const;

    [[nodiscard]] float getLength() const;
    void normalise();
    static Vector3 getCrossProduct(Vector3 const &vector1, Vector3 const &vector2);
};
#endif //VECTOR3_HPP
