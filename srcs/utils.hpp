#ifndef UTILS_HPP
# define UTILS_HPP

# include <cmath>
# include <iostream>
# include "GLFW/glfw3.h"

float convertToRadians(float angle);
float convertToDegrees(float angle);
void printToConsole(const std::string& text);
void scopError(const std::string& text, const char* error);

#endif //UTILS_HPP
