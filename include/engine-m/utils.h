#pragma once

#include <cstdint>

#include "core.h"
#include "vector/vector2d.h"
#include "vector/vector3d.h"

namespace EngineM {

    ENGINE_M_API bool equals(float, float);

    ENGINE_M_API int clamp(int, int, int);

    ENGINE_M_API float clamp(float, float, float);

    ENGINE_M_API float degreesToRadians(float);

    ENGINE_M_API float radiansToDegrees(float);

    ENGINE_M_API float lerp(float, float, float);
    ENGINE_M_API Vector2d lerp(const Vector2d &, const Vector2d &, float);
    ENGINE_M_API Vector3d lerp(const Vector3d &, const Vector3d &, float);

    ENGINE_M_API uint64_t factorial(uint64_t);

    ENGINE_M_API float binomialCoefficient(int, int);
}
