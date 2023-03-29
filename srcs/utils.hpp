#ifndef UTILS_HPP
# define UTILS_HPP

# include "glad/glad.h"
# include "GLFW/glfw3.h"

# include <cmath>
# include <iostream>
# include <sstream>
# include <vector>

float convertToRadians(float angle);
float convertToDegrees(float angle);
std::vector<std::string> strSplit(const std::string& str, char delim);
void printToConsole(const std::string& text);
void scopError(const std::string& text, const char* error);

#endif //UTILS_HPP
