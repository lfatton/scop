#include "utils.hpp"

float convertToRadians(float angle) {
    return angle * (static_cast<float>(M_PI) / 180.f);
}

float convertToDegrees(float angle) {
    return angle * (180.f / static_cast<float>(M_PI));
}
