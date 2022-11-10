#ifndef CAMERA_HPP
# define CAMERA_HPP

#include "Vector.hpp"
#include "Matrix.hpp"

class Camera {
private:
public:
    Vector position{}, target{}, xAxis{}, yAxis{}, zAxis{};

    Camera(Vector &givenPosition, Vector &givenFront);

    Camera& operator =(Camera const &cameraToCopy);
};

#endif //CAMERA_HPP
