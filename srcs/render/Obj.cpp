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

        this->mVertices.push_back(vertex);
    } else if (line[1] == 't') {
        Vector2 vt;
        matches = std::sscanf(&(line[0]),
                              "vt %f %f\n", &vt.x, &vt.y);

        if (matches != 2)
            scopError("error: bad vertex texture line format for: " + line +
                      "\n example of good vertex texture format: vt 0.748573 0.750412",
                      "");

        this->mUVs.push_back(vt);
        this->mHasUVs = true;
    } else if (line[1] == 'n') {
        Vector3 vn;
        matches = std::sscanf(&(line[0]),
                              "vn %f %f %f\n", &vn.x, &vn.y, &vn.z);

        if (matches != 3)
            scopError("error: bad vertex normal line format for: " + line +
                      "\n example of good vertex normal line format: vn 0.000000 0.000000 -1.000000",
                      "");

        this->mNormals.push_back(vn);
        this->mHasNormals = true;
    } else {
        scopError("error: bad vertex line format for: " + line +
                  "\n example of good vertex line format: v -0.227475 -0.745504 2.843098",
                  "");
    }
}

void Obj::readFaceLine(const std::string &line) {
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

            for (unsigned int index: indices) {
                if (index <= 0 || index > this->mVertices.size())
                    scopError("error: out of index for face line: " + line, "");
                this->mVerticesIndices.push_back(index - 1);
            }

            if (length == 5) {
                try {
                    indices[0] = std::stoi(splitIndices[1]);
                    indices[1] = std::stoi(splitIndices[3]);
                    indices[2] = std::stoi(splitIndices[4]);
                } catch (std::exception &e) {
                    scopError("error: cannot parse line: " + line, e.what());
                }

                for (unsigned int index: indices) {
                    if (index <= 0 || index > this->mVertices.size())
                        scopError("error: out of index for face line: " + line, "");
                    this->mVerticesIndices.push_back(index - 1);
                }
            }
        } else {
            int matches{};
            unsigned int indexVertex[3]{}, indexUV[3]{}, indexNormal[3]{};

            for (unsigned int i = 0; i < 3; i++) {
                if (!this->mHasUVs)
                    matches += sscanf(splitIndices[i + 1].c_str(), "%d//%d", &indexVertex[i], &indexNormal[i]);
                else
                    matches += sscanf(splitIndices[i + 1].c_str(), "%d/%d/%d", &indexVertex[i], &indexUV[i],
                                      &indexNormal[i]);
            }

            if (matches != 6 && matches != 9) {
                scopError("error: bad face line format for: " + line +
                          "\n example of good face line format: f 1/2/8 3/13/8 4/14/8",
                          "");
            }

            for (unsigned int i = 0; i < 3; i++) {
                if ((indexVertex[i] <= 0 || indexVertex[i] > this->mVertices.size()) ||
                    (indexNormal[i] <= 0 || indexNormal[i] > this->mNormals.size()))
                    scopError("error: out of index for face line: " + line, "");
                this->mVerticesIndices.push_back(indexVertex[i] - 1);
                this->mNormalsIndices.push_back(indexNormal[i] - 1);

                if (this->mHasUVs) {
                    if (indexUV[i] <= 0 || indexUV[i] > this->mUVs.size())
                        scopError("error: out of index for face line: " + line, "");
                    this->mUVsIndices.push_back(indexUV[i] - 1);
                }
            }

            if (length == 5) {
                matches = 0;

                if (!this->mHasUVs) {
                    matches += sscanf(splitIndices[1].c_str(), "%d//%d", &indexVertex[0], &indexNormal[0]);
                    matches += sscanf(splitIndices[3].c_str(), "%d//%d", &indexVertex[1], &indexNormal[1]);
                    matches += sscanf(splitIndices[4].c_str(), "%d//%d", &indexVertex[2], &indexNormal[2]);

                } else {
                    matches += sscanf(splitIndices[1].c_str(), "%d/%d/%d", &indexVertex[0], &indexUV[0],
                                      &indexNormal[0]);
                    matches += sscanf(splitIndices[3].c_str(), "%d/%d/%d", &indexVertex[1], &indexUV[1],
                                      &indexNormal[1]);
                    matches += sscanf(splitIndices[4].c_str(), "%d/%d/%d", &indexVertex[2], &indexUV[2],
                                      &indexNormal[2]);
                }

                if (matches != 6 && matches != 9) {
                    scopError("error: bad face line format for: " + line +
                              "\n example of good face line format: f 1/2/8 3/13/8 4/14/8",
                              "");
                }

                for (unsigned int i = 0; i < 3; i++) {
                    if ((indexVertex[i] <= 0 || indexVertex[i] > this->mVertices.size()) ||
                        (indexNormal[i] <= 0 || indexNormal[i] > this->mNormals.size()))
                        scopError("error: out of index for face line: " + line, "");
                    this->mVerticesIndices.push_back(indexVertex[i] - 1);
                    this->mNormalsIndices.push_back(indexNormal[i] - 1);

                    if (this->mHasUVs) {
                        if (indexUV[i] <= 0 || indexUV[i] > this->mUVs.size())
                            scopError("error: out of index for face line: " + line, "");
                        this->mUVsIndices.push_back(indexUV[i] - 1);
                    }
                }
            }
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

void Obj::indexVBO() {
    if (this->mHasUVs) {
        for (unsigned int index: this->mUVsIndices) {
            Vector2 uv = this->mUVs[index];
            this->mIndexedUVs.push_back(uv);
        }
    }

    for (unsigned int index: this->mNormalsIndices) {
        Vector3 normal = this->mNormals[index];
        this->mIndexedNormals.push_back(normal);
    }

    for (unsigned int index: this->mVerticesIndices) {
        Vector3 vertex = this->mVertices[index];
        this->mIndexedVertices.push_back(vertex);
    }
}


void Obj::generateBuffers() {
    glGenVertexArrays(1, &this->mVAO);
    glGenBuffers(1, &this->mVBO);

    if (this->mVAO < 0 || this->mVBO < 0)
        scopError("error: buffer creation failed", "");

    this->computeCenter();

    if (this->mHasNormals) {
        this->indexVBO();

        glBindVertexArray(this->mVAO);

        if (!this->mIndexedVertices.empty()) {
            glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
            glBufferData(GL_ARRAY_BUFFER, this->mIndexedVertices.size() * sizeof(Vector3),
                         this->mIndexedVertices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            if (this->mHasUVs && !this->mIndexedUVs.empty()) {
                glGenBuffers(1, &this->mUVsVBO);

                if (this->mUVsVBO < 0)
                    scopError("error: buffer creation failed", "");

                glBindBuffer(GL_ARRAY_BUFFER, this->mUVsVBO);
                glBufferData(GL_ARRAY_BUFFER, this->mIndexedUVs.size() * sizeof(Vector2),
                             this->mIndexedUVs.data(), GL_STATIC_DRAW);
            }
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

            if (!this->mIndexedNormals.empty()) {
                glGenBuffers(1, &this->mNormalsVBO);

                if (this->mNormalsVBO < 0)
                    scopError("error: buffer creation failed", "");

                glBindBuffer(GL_ARRAY_BUFFER, this->mNormalsVBO);
                glBufferData(GL_ARRAY_BUFFER, this->mIndexedNormals.size() * sizeof(Vector3),
                             this->mIndexedNormals.data(), GL_STATIC_DRAW);

                glEnableVertexAttribArray(2);
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            }
        }
    } else {
        glGenBuffers(1, &this->mEBO);

        if (this->mEBO < 0)
            scopError("error: buffer creation failed", "");

        glBindVertexArray(this->mVAO);

        if (!this->mVertices.empty()) {
            glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
            glBufferData(GL_ARRAY_BUFFER, this->mVertices.size() * sizeof(Vector3),
                         this->mVertices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        }

        if (!this->mVerticesIndices.empty()) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mVerticesIndices.size() * sizeof(unsigned short),
                         this->mVerticesIndices.data(), GL_STATIC_DRAW);
        }
    }

}

void	Obj::computeCenter() {
    Vector3	min, max = this->mVertices[0];
    Vector3 center{};

    for (unsigned int i = 1; i < this->mVertices.size(); i++) {
        min.x = this->mVertices[i].x < min.x ? this->mVertices[i].x : min.x;
        min.y = this->mVertices[i].y < min.y ? this->mVertices[i].y : min.y;
        min.z = this->mVertices[i].z < min.z ? this->mVertices[i].z : min.z;
        max.x = this->mVertices[i].x > max.x ? this->mVertices[i].x : max.x;
        max.y = this->mVertices[i].y > max.y ? this->mVertices[i].y : max.y;
        max.z = this->mVertices[i].z > max.z ? this->mVertices[i].z : max.z;
    }

    center = (min + max) / 2.0;

    for (unsigned int i = 0; i < this->mVertices.size(); i++) {
        this->mVertices[i] = this->mVertices[i] - center;
    }

}

void Obj::draw() const {
    glBindVertexArray(this->mVAO);

    if (this->mHasNormals) {
        glDrawArrays(GL_TRIANGLES, 0, this->mIndexedVertices.size());
    } else {
        glDrawElements(GL_TRIANGLES, this->mVerticesIndices.size(), GL_UNSIGNED_SHORT, nullptr);
    }
}