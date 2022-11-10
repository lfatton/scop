#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cmath>

class Vector {
private:
public:
    float x, y, z, w;

    explicit Vector(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);

    Vector operator +(Vector const &addedVector) const;
    Vector operator -(Vector const &subtrahendVector) const;
    float operator *(Vector const &multiplierVector) const;
    Vector operator *(float multiplier) const;
    Vector& operator =(Vector const &vectorToCopy);

    [[nodiscard]] float getLength() const;
    void getUnitVector();
    static Vector getCrossProduct(Vector const &vector1, Vector const &vector2);
};

#endif //VECTOR_HPP