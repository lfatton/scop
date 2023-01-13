#include "utils.hpp"

float convertToRadians(float angle) {
    return angle * (static_cast<float>(M_PI) / 180.f);
}

float convertToDegrees(float angle) {
    return angle * (180.f / static_cast<float>(M_PI));
}

void printToConsole(const std::string& text) {
    std::cout << text << std::endl;
}

void scopError(const std::string& text, const char* error) {
    std::cerr << text << std::endl << error << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
}