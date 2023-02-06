#include "utils.hpp"

float convertToRadians(float angle) {
    return angle * (static_cast<float>(M_PI) / 180.f);
}

float convertToDegrees(float angle) {
    return angle * (180.f / static_cast<float>(M_PI));
}

std::vector<std::string> strSplit(const std::string& str, const char delim) {
    std::vector<std::string> result;
    std::string item;
    std::stringstream strStream (str);

    while (getline(strStream, item, delim)) {
        result.push_back(item);
    }

    return result;
}

void printToConsole(const std::string& text) {
    std::cout << text << std::endl;
}

void scopError(const std::string& text, const char* error) {
    std::cerr << text << std::endl << error << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
}