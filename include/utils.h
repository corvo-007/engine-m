#pragma once

#include "core.h"

#include <cmath>
#include <algorithm>
#include "constants.h"
#include "vector/vector2d.h"
#include "vector/vector3d.h"

namespace MathEngine {

    MATH_ENGINE_API bool equals(const float, const float);

    MATH_ENGINE_API int clamp(const int, const int, const int);

    MATH_ENGINE_API float clamp(const float, const float, const float);

    MATH_ENGINE_API float degreesToRadians(const float);

    MATH_ENGINE_API float radiansToDegrees(const float);

    MATH_ENGINE_API float lerp(const float, const float, const float);
    MATH_ENGINE_API Vector2d lerp(const Vector2d &, const Vector2d &, const float);
    MATH_ENGINE_API Vector3d lerp(const Vector3d &, const Vector3d &, const float);
}
