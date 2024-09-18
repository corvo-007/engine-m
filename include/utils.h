#pragma once

#include "core.h"

#include <cmath>
#include <algorithm>
#include "constants.h"

namespace MathEngine {

    MATH_ENGINE_API bool equals(const float, const float);

    MATH_ENGINE_API int clamp(const int, const int, const int);

    MATH_ENGINE_API float clamp(const float, const float, const float);

    MATH_ENGINE_API float degreesToRadians(const float);

    MATH_ENGINE_API float radiansToDegrees(const float);
}
