#pragma once

#include "core.h"
#include "vector/vector2d.h"
#include "vector/vector3d.h"

namespace MathEngine {

    MATH_ENGINE_API bool equals(float, float);

    MATH_ENGINE_API int clamp(int, int, int);

    MATH_ENGINE_API float clamp(float, float, float);

    MATH_ENGINE_API float degreesToRadians(float);

    MATH_ENGINE_API float radiansToDegrees(float);

    MATH_ENGINE_API float lerp(float, float, float);
    MATH_ENGINE_API Vector2d lerp(const Vector2d &, const Vector2d &, float);
    MATH_ENGINE_API Vector3d lerp(const Vector3d &, const Vector3d &, float);
}
