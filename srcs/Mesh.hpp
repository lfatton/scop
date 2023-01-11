#ifndef MESH_HPP
# define MESH_HPP

# include <vector>
# include "Vertex.hpp"
# include "Face.hpp"
# include "Shader.hpp"

class Mesh {
private:
    std::vector<float> mVerticesToArray{};
    std::vector<unsigned int> mIndicesToArray{};
    unsigned int mVBO{}, mEBO{}, mVAO{};
public:
    std::vector<Vertex> vertices{};
    std::vector<Face> indices{};

    Mesh(std::vector<Vertex> vertices, std::vector<Face> indices);
    ~Mesh();

    void Draw();
};

#endif //MESH_HPP
