#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <fstream>
# include <sstream>

# include "utils.hpp"

class Parser {
private:
    std::string mPath{};

    void readFile();
public:

    void parse(std::string path);
};


#endif //PARSER_HPP
