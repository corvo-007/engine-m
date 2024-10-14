#pragma once

#include <memory>

#include "core.h"
#include "vector/vector3d.h"
#include "frame.h"

namespace MathEngine {

    class MATH_ENGINE_API Curve {
    public:
        [[nodiscard]] virtual Vector3d evaluate(float) const = 0;
        [[nodiscard]] virtual Vector3d tangentAt(float) const = 0;
        [[nodiscard]] virtual Vector3d accelerationAt(float) const = 0;
        [[nodiscard]] virtual Vector3d normalAt(float) const = 0;

        [[nodiscard]] virtual std::pair<std::unique_ptr<Curve>, std::unique_ptr<Curve>> split(float) const = 0;

        [[nodiscard]] virtual Frame getFrenetFrame(float) const = 0;
        [[nodiscard]] virtual Frame getRMF(float, int) const = 0;

        [[nodiscard]] virtual float length() const = 0;

        virtual ~Curve() = default;
    };
}