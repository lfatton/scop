#ifndef LOADER_BMP_HPP
# define LOADER_BMP_HPP

# include <string>
# include <fstream>

# include "../utils.hpp"

class LoaderBMP {
private:
    const char *mPath{};
    unsigned char mHeader[54]{};
    unsigned int mDataPos{}, mWidth{}, mHeight{}, mSize{};
    unsigned char * mData{};

    void parseBMP();
public:
    LoaderBMP(const char* path);
    GLuint bindTexture();
};


#endif //LOADER_BMP_HPP
