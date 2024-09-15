#pragma once

#include <cmath>
#include <algorithm>
#include "constants.h"

namespace MathEngine {

    bool equals(const float, const float);

    int clamp(const int, const int, const int);

    float clamp(const float, const float, const float);

    float degreesToRadians(const float);

    float radiansToDegrees(const float);
}
