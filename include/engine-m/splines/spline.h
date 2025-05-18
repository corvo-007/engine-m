#pragma once

#include <memory>
#include <vector>

#include "engine-m/core.h"
#include "engine-m/vector/vector3d.h"
#include "engine-m/frame.h"

namespace EngineM {
    class ENGINE_M_API Spline {
    protected:
        std::vector<Vector3d> points;

    public:
        Spline() = default;
        explicit Spline(const std::vector<Vector3d> &);
        Spline(const Spline &) = default;

    protected:
        [[nodiscard]] float legendreGaussQuadratureLength() const;

    public:
        [[nodiscard]] virtual Vector3d evaluateAt(float) const = 0;
        [[nodiscard]] virtual Vector3d tangentAt(float) const = 0;
        [[nodiscard]] virtual Vector3d accelerationAt(float) const = 0;
        [[nodiscard]] virtual Vector3d normalAt(float) const = 0;

        [[nodiscard]] virtual std::pair<std::unique_ptr<Spline>, std::unique_ptr<Spline>> split(float) const = 0;

        [[nodiscard]] Frame getFrenetFrame(float) const;
        [[nodiscard]] Frame getRMF(float, int) const;

        [[nodiscard]] float length() const;

        [[nodiscard]] virtual uint32_t segments() const = 0;

        virtual ~Spline() = default;
    };
}
