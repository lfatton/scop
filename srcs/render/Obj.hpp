#ifndef OBJ_HPP
# define OBJ_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <cstring>
# include <vector>
# include <map>

# include "../utils.hpp"
# include "../libmath/Vector3.hpp"
# include "../libmath/Vector2.hpp"

struct PackedVertex{
    Vector3 position;
    Vector2 uv;
    Vector3 normal;
    bool operator<(const PackedVertex that) const{
        return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
    };
};

class Obj {
private:
    std::string mPath{};
    std::vector<Vector3> mVertices{}, mIndexedVertices{}, mNormals{}, mIndexedNormals{};
    std::vector<Vector2> mUVs{}, mIndexedUVs{};
    std::vector<unsigned short> mVerticesIndices{}, mUVsIndices{}, mNormalsIndices{}, mIndices{};
    bool mHasUVs{}, mHasNormals{};
    GLuint mVBO{}, mUVsVBO{}, mNormalsVBO{}, mEBO{}, mVAO{};

    void readVertexLine(std::string line);
    void readFaceLine(const std::string& line);
    void parseFile();
    void indexVBO();
    void generateBuffers();
    void computeCenter();
public:
    Obj();
    ~Obj();

    void load(std::string path);
    void draw() const;
};


#endif //OBJ_HPP
