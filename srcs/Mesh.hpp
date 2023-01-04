#ifndef MESH_HPP
# define MESH_HPP

# include <vector>
# include "Vertex.hpp"
# include "Shader.hpp"

class Mesh {
private:
    unsigned int mVBO{}, mVAO{}, mEBO{};
public:
    std::vector<Vertex> vertices{};
    std::vector<unsigned int> indices{};

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    ~Mesh();

    std::vector<float> getVerticesAsFloatArray() const;
    void Draw(Shader &shader);
};

#endif //MESH_HPP
