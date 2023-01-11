#ifndef VERTEX_HPP
# define VERTEX_HPP

# include <vector>
# include "glad/glad.h"
# include "GLFW/glfw3.h"
# include "Vector.hpp"

class Vertex {
private:
public:
    Vector position{}, textureCoordinates{}, normal{};

    explicit Vertex(Vector position = Vector());
};

#endif //VERTEX_HPP
