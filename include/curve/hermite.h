#pragma once

#include "core.h"
#include "curve.h"
#include <vector>
#include "vector/vector3d.h"

namespace MathEngine {

    class MATH_ENGINE_API HermiteCurve : public Curve {
        Vector3d p1;
        Vector3d p2;
        Vector3d v1;
        Vector3d v2;

    public:
        HermiteCurve() = default;
        HermiteCurve(const Vector3d &, const Vector3d &, const Vector3d &, const Vector3d &);
        HermiteCurve(const HermiteCurve &) = default;

    private:
        [[nodiscard]] float legendreGaussQuadratureLength() const;

    public:
        HermiteCurve& operator=(const HermiteCurve &) = default;

        [[nodiscard]] Vector3d evaluate(float) const override;
        [[nodiscard]] Vector3d tangentAt(float) const override;
        [[nodiscard]] Vector3d accelerationAt(float) const override;
        [[nodiscard]] Vector3d normalAt(float) const override;

        [[nodiscard]] std::pair<std::unique_ptr<Curve>, std::unique_ptr<Curve>> split(float) const override;

        [[nodiscard]] Frame getFrenetFrame(float) const override;
        [[nodiscard]] Frame getRMF(float, int) const override;

        [[nodiscard]] float length() const override;

        [[nodiscard]] std::pair<Vector3d, Vector3d> getPoints() const;
        [[nodiscard]] Vector3d getStart() const;
        [[nodiscard]] Vector3d getEnd() const;

        void setPoints(const Vector3d &, const Vector3d &);
        void setStart(const Vector3d &);
        void setEnd(const Vector3d &);

        [[nodiscard]] std::pair<Vector3d, Vector3d> getTangents() const;
        [[nodiscard]] Vector3d getStartTangent() const;
        [[nodiscard]] Vector3d getEndTangent() const;

        void setTangents(const Vector3d &, const Vector3d &);
        void setStartTangent(const Vector3d &);
        void setEndTangent(const Vector3d &);
    };
}
