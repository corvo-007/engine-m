#include "utils.h"

namespace MathEngine {

    bool equals(const float a, const float b) {
        return fabs(a - b) < epsilon;
    }

    int clamp(const int value, const int min, const int max) {
        return std::max(min, std::min(value, max));
    }

    float clamp(const float value, const float min, const float max) {
        return std::max(min, std::min(value, max));
    }

    float degreesToRadians(const float degrees) {
        return degrees * PI / 180;
    }

    float radiansToDegrees(const float radians) {
        return radians * 180 / PI;
    }
}
