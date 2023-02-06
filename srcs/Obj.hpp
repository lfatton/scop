#ifndef OBJ_HPP
# define OBJ_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <cstring>
# include <vector>

# include "utils.hpp"
# include "Vector3.hpp"
# include "Vector2.hpp"

class Obj {
private:
    std::string mPath{};
    bool mHasUVs{}, mHasNormals{};
    std::vector<float> mVerticesToArray{}, mUVsToArray{}, mNormalsToArray{};
    std::vector<unsigned int> mIndicesToArray{};
    unsigned int mVBO{}, mUVsVBO{}, mNormalsVBO{}, mEBO{}, mVAO{};

    void readVertexLine(std::string line);
    void readFaceLine(const std::string& line);
    void parseFile();
    void generateBuffers();
public:
    std::vector<Vector3> tempVertices{}, indexedVertices{}, tempNormals{}, indexedNormals{};
    std::vector<Vector2> tempUVs{}, indexedUVs{};
    std::vector<unsigned int> indicesVertices, indicesUVs, indicesNormals;

    Obj();
    ~Obj();

    void load(std::string path);
    void draw() const;
};


#endif //OBJ_HPP
