#pragma once

#include <memory>

#include "engine-m/core.h"
#include "engine-m/vector/vector3d.h"
#include "engine-m/frame.h"

namespace EngineM {

    class ENGINE_M_API Curve {
    public:
        [[nodiscard]] virtual vec3f evaluate(float) const = 0;
        [[nodiscard]] virtual vec3f tangentAt(float) const = 0;
        [[nodiscard]] virtual vec3f accelerationAt(float) const = 0;
        [[nodiscard]] virtual vec3f normalAt(float) const = 0;

        [[nodiscard]] virtual std::pair<std::unique_ptr<Curve>, std::unique_ptr<Curve>> split(float) const = 0;

        [[nodiscard]] virtual Frame getFrenetFrame(float) const = 0;
        [[nodiscard]] virtual Frame getRMF(float, int) const = 0;

        [[nodiscard]] virtual float length() const = 0;

        virtual ~Curve() = default;
    };
}