#include "utils.hpp"

float convertToRadians(float angle) {
    return angle * (static_cast<float>(M_PI) / 180.0f);
}

float convertToDegrees(float angle) {
    return angle * (180.0f / static_cast<float>(M_PI));
}
