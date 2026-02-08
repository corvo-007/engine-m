#include "engine-m/utils.h"

#include <cmath>

#include "engine-m/constants.h"

namespace EngineM {

    bool equals(const float a, const float b) {
        return std::fabs(a - b) < epsilon;
    }

    int clamp(const int value, const int min, const int max) {
        return std::max(min, std::min(value, max));
    }

    float clamp(const float value, const float min, const float max) {
        return std::max(min, std::min(value, max));
    }

    double degreesToRadians(const double degrees) {
        return degrees * PI / 180;
    }

    float radiansToDegrees(const float radians) {
        return radians * 180 / PI;
    }

    float lerp(const float p1, const float p2, const float t) {
        return (1 - t) * p1 + t * p2;
    }

    vec2f lerp(const vec2f &p1, const vec2f &p2, const float t) {
        return p1 * (1 - t) + p2 * t;
    }

    vec3f lerp(const vec3f &p1, const vec3f &p2, const float t) {
        return p1 * (1 - t) + p2 * t;
    }

    uint64_t factorial(const uint64_t n) {
        uint64_t fact = 1;
        for (uint64_t i = 1; i <= n; i++) {
            fact *= i;
        }
        return fact;
    }

    float binomialCoefficient(const int n, const int k) {
        return static_cast<float>(factorial(n)) / static_cast<float>(factorial(k) * factorial(n - k));
    }
}
