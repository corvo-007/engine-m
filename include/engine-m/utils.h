#pragma once

#include <cstdint>

#include "core.h"
#include "vector/vector.h"

namespace EngineM {

    ENGINE_M_API bool equals(float, float);

    ENGINE_M_API int clamp(int, int, int);

    ENGINE_M_API float clamp(float, float, float);

    ENGINE_M_API double degreesToRadians(double);

    ENGINE_M_API float radiansToDegrees(float);

    ENGINE_M_API float lerp(float, float, float);
    ENGINE_M_API vec2f lerp(const vec2f &, const vec2f &, float);
    ENGINE_M_API vec3f lerp(const vec3f &, const vec3f &, float);

    ENGINE_M_API uint64_t factorial(uint64_t);

    ENGINE_M_API float binomialCoefficient(int, int);
}
