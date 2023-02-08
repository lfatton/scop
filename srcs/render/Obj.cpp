#include "Obj.hpp"

Obj::Obj() = default;

Obj::~Obj() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mEBO);

    if (this->mHasNormals)
        glDeleteBuffers(1, &mNormalsVBO);
    if (this->mHasUVs)
        glDeleteBuffers(1, &mUVsVBO);
}


void Obj::readVertexLine(std::string line) {
    int matches;

    if (line[1] == ' ') {
        Vector3 vertex;
        matches = std::sscanf(&(line[0]),
                              "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

        if (matches != 3)
            scopError("error: bad vertex line format for: " + line +
                      "\n example of good vertex line format: v -0.227475 -0.745504 2.843098",
                      "");

        this->tempVertices.push_back(vertex);
    } else if (line[1] == 't') {
        Vector2 vt;
        matches = std::sscanf(&(line[0]),
                              "vt %f %f\n", &vt.x, &vt.y);

        if (matches != 2)
            scopError("error: bad vertex texture line format for: " + line +
                      "\n example of good vertex texture format: vt 0.748573 0.750412",
                      "");

        this->tempUVs.push_back(vt);
        this->mHasUVs = true;
    } else if (line[1] == 'n') {
        Vector3 vn;
        matches = std::sscanf(&(line[0]),
                              "vn %f %f %f\n", &vn.x, &vn.y, &vn.z);

        if (matches != 3)
            scopError("error: bad vertex normal line format for: " + line +
                      "\n example of good vertex normal line format: vn 0.000000 0.000000 -1.000000",
                      "");

        this->tempNormals.push_back(vn);
        this->mHasNormals = true;
    } else {
        scopError("error: bad vertex line format for: " + line +
                  "\n example of good vertex line format: v -0.227475 -0.745504 2.843098",
                  "");
    }
}

void Obj::readFaceLine(const std::string& line) {
    const std::vector<std::string> splitIndices = strSplit(line, ' ');
    unsigned int length = splitIndices.size();

    if (length == 4 || length == 5) {
        if (!this->mHasUVs && !this->mHasNormals) {
            unsigned int indices[3]{};

            try {
                for (unsigned int i = 0; i < 3; i++) {
                    indices[i] = std::stoi(splitIndices[i + 1]);
                }
            } catch (std::exception &e) {
                scopError("error: cannot parse line: " + line, e.what());
            }

            for (unsigned int index : indices) {
                if (index <= 0 || index > this->tempVertices.size())
                    scopError("error: out of index for face line: " + line, "");
                this->indicesVertices.push_back(index);
            }

            if (length == 5) {
                try {
                    indices[0] = std::stoi(splitIndices[1]);
                    indices[1] = std::stoi(splitIndices[3]);
                    indices[2] = std::stoi(splitIndices[4]);
                } catch (std::exception &e) {
                    scopError("error: cannot parse line: " + line, e.what());
                }

                for (unsigned int index : indices) {
                    if (index <= 0 || index > this->tempVertices.size())
                        scopError("error: out of index for face line: " + line, "");
                    this->indicesVertices.push_back(index);
                }
            }
        } else {
            int matches{};
            unsigned int indexVertex[3]{}, indexUV[3]{}, indexNormal[3]{};

            for (unsigned int i = 1; i < 4; i++) {
                if (!this->mHasUVs)
                    matches += sscanf(splitIndices[i].c_str(), "%d//%d", &indexVertex[i - 1], &indexNormal[i - 1]);
                else
                    matches += sscanf(splitIndices[i].c_str(), "%d/%d/%d", &indexVertex[i - 1], &indexUV[i - 1], &indexNormal[i - 1]);
            }

            if (matches != 6 && matches != 9) {
                scopError("error: bad face line format for: " + line +
                          "\n example of good face line format: f 1/2/8 3/13/8 4/14/8",
                          "");
            }

            for (unsigned int i = 0; i < 3; i++) {
                if ((indexVertex[i] <= 0 || indexVertex[i] > this->tempVertices.size()) ||
                        (indexNormal[i] <= 0 || indexNormal[i] > this->tempNormals.size()))
                    scopError("error: out of index for face line: " + line, "");
                this->indicesVertices.push_back(indexVertex[i]);
                this->indicesNormals.push_back(indexVertex[i]);

                if (this->mHasUVs) {
                    if (indexUV[i] <= 0 || indexUV[i] > this->tempUVs.size())
                        scopError("error: out of index for face line: " + line, "");
                    this->indicesUVs.push_back(indexVertex[i]);
                }
            }

            if (length == 5) {
                matches = 0;

                if (!this->mHasUVs) {
                    matches += sscanf(splitIndices[1].c_str(), "%d//%d", &indexVertex[0], &indexNormal[0]);
                    matches += sscanf(splitIndices[3].c_str(), "%d//%d", &indexVertex[1], &indexNormal[1]);
                    matches += sscanf(splitIndices[4].c_str(), "%d//%d", &indexVertex[2], &indexNormal[2]);

                } else {
                    matches += sscanf(splitIndices[1].c_str(), "%d/%d/%d", &indexVertex[0], &indexUV[0], &indexNormal[0]);
                    matches += sscanf(splitIndices[3].c_str(), "%d/%d/%d", &indexVertex[1], &indexUV[1], &indexNormal[1]);
                    matches += sscanf(splitIndices[4].c_str(), "%d/%d/%d", &indexVertex[2], &indexUV[2], &indexNormal[2]);
                }

                if (matches != 6 && matches != 9) {
                    scopError("error: bad face line format for: " + line +
                              "\n example of good face line format: f 1/2/8 3/13/8 4/14/8",
                              "");
                }

                for (unsigned int i = 0; i < 3; i++) {
                    if ((indexVertex[i] <= 0 || indexVertex[i] > this->tempVertices.size()) ||
                            (indexNormal[i] <= 0 || indexNormal[i] > this->tempNormals.size()))
                        scopError("error: out of index for face line: " + line, "");
                    this->indicesVertices.push_back(indexVertex[i]);
                    this->indicesNormals.push_back(indexVertex[i]);

                    if (this->mHasUVs) {
                        if (indexUV[i] <= 0 || indexUV[i] > this->tempUVs.size())
                            scopError("error: out of index for face line: " + line, "");
                        this->indicesUVs.push_back(indexVertex[i]);
                    }
                }
            }

            for (unsigned int index: this->indicesNormals) {
                Vector3 normal = this->tempNormals[index - 1];
                this->indexedNormals.push_back(normal);
            }

            if (this->mHasUVs) {
                for (unsigned int index: this->indicesUVs) {
                    Vector2 uv = this->tempUVs[index - 1];
                    this->indexedUVs.push_back(uv);
                }
            }
        }

        for (unsigned int index: this->indicesVertices) {
            Vector3 vertex = this->tempVertices[index - 1];
            this->indexedVertices.push_back(vertex);
        }
    } else {
        scopError("error: bad face line format for: " + line +
                  "\n example of good face (without vt and vn) line format: f 34 27 19 OR f 8 14 7",
                  "");
    }
}

void Obj::parseFile() {
    std::ifstream objFile;

    objFile.open(this->mPath);

    if (!objFile)
        scopError("error: cannot read obj file given", "");

    for (std::string line; std::getline(objFile, line);) {
        if (line[0] == 'v')
            this->readVertexLine(line);
        else if (line[0] == 'f')
            this->readFaceLine(line);
    }

    objFile.close();
}

void Obj::load(std::string path) {
    this->mPath = std::move(path);

    try {
        this->parseFile();
        this->generateBuffers();
    } catch (std::ifstream::failure &e) {
        scopError("error: cannot read obj file given", e.what());
    }
}

void Obj::generateBuffers() {
    glGenVertexArrays(1, &this->mVAO);
    glGenBuffers(1, &this->mVBO);
    glGenBuffers(1, &this->mEBO);

    if (this->mVAO < 0 || this->mVBO < 0 ||  this->mEBO < 0)
        scopError("error: buffer creation failed", "");

    if (!this->indexedVertices.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
        glBufferData(GL_ARRAY_BUFFER, this->indexedVertices.size() * sizeof(float),
                     this->indexedVertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    if (this->mHasNormals && !this->indexedNormals.empty()) {
        glGenBuffers(1, &this->mNormalsVBO);
        if (this->mNormalsVBO < 0)
            scopError("error: buffer creation failed", "");

        glBindBuffer(GL_ARRAY_BUFFER, this->mNormalsVBO);
        glBufferData(GL_ARRAY_BUFFER, this->indexedNormals.size() * sizeof(float) * 3,
                     this->indexedNormals.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    if (this->mHasUVs && !this->indexedUVs.empty()) {
        glGenBuffers(1, &this->mUVsVBO);
        if (this->mUVsVBO < 0)
            scopError("error: buffer creation failed", "");

        glBindBuffer(GL_ARRAY_BUFFER, this->mUVsVBO);
        glBufferData(GL_ARRAY_BUFFER, this->indexedUVs.size() * sizeof(float) * 2,
                     this->indexedUVs.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    if (!this->indicesVertices.empty()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesVertices.size() * sizeof(unsigned int),
                     this->indicesVertices.data(), GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Obj::draw() const {
    if (this->mVBO != 0) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    if (this->mHasNormals && this->mNormalsVBO != 0) {
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, this->mNormalsVBO);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }


    if (this->mHasUVs && this->mUVsVBO != 0) {
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, this->mUVsVBO);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    glBindVertexArray(this->mVAO);
    //std::cout << "NB " << this->indicesVertices.size() << std::endl;

    //glDrawElements(GL_TRIANGLES, this->indicesVertices.size(), GL_UNSIGNED_INT, nullptr);
    glDrawArrays(GL_TRIANGLES,0, this->indicesVertices.size());
}