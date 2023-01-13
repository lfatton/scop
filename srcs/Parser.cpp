#include "Parser.hpp"

void Parser::parse(std::string path) {
    mPath = path;

    try {
        readFile();
    } catch (std::ifstream::failure &e) {
       scopError("error: cannot read obj file given", e.what());
    }
}

void Parser::readFile() {
    std::ifstream file;

    file.open(this->mPath);
    if (!file)
        scopError("error: cannot read obj file given", "");

    file.close();
}

