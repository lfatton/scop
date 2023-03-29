#include "LoaderBMP.hpp"

LoaderBMP::LoaderBMP(const char* path) {
    this->mPath = path;

    try {
        this->parseBMP();
    } catch (std::ifstream::failure &e) {
        scopError("error: cannot read BMP given", e.what());
    }
}

GLuint LoaderBMP::bindTexture() {
    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->mWidth, this->mHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, this->mData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
}

void LoaderBMP::parseBMP() {
    FILE *bmp = fopen(this->mPath, "rb");

    if (!bmp)
        scopError("error: cannot read BMP given", "");

    if (fread(this->mHeader, 1, 54, bmp) != 54 )
        scopError("error: BMP header bad format", "");

    if (this->mHeader[0] != 'B' || this->mHeader[1] != 'M')
        scopError("error: BMP header bad format", "");

    this->mDataPos = *(int*)&(this->mHeader[0x0A]);
    this->mSize = *(int*)&(this->mHeader[0x22]);
    this->mWidth = *(int*)&(this->mHeader[0x12]);
    this->mHeight = *(int*)&(this->mHeader[0x16]);

    if (this->mSize == 0)
        this->mSize = this->mWidth * this->mHeight * 3;

    if (this->mDataPos == 0)
        this->mDataPos = 54;

    this->mData = new unsigned char[this->mSize];
    fread(this->mData, 1,this->mSize,bmp);

    fclose(bmp);
}