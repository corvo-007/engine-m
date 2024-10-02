#pragma once

#include <vector>

#include "core.h"
#include "vector/vector3d.h"
#include "frame.h"

namespace MathEngine {

    class MATH_ENGINE_API BezierCurve {
        int degree;
        std::vector<Vector3d> points;

    public:
        BezierCurve() = delete;
        explicit BezierCurve(int);
        BezierCurve(int, const std::vector<Vector3d> &);
        BezierCurve(const BezierCurve &) = default;

    private:
        [[nodiscard]] Vector3d deCasteljau(float) const;

        [[nodiscard]] std::pair<BezierCurve, BezierCurve> deCasteljauSplit(float) const;

        [[nodiscard]] float length(const Vector3d &, const Vector3d &, float, float) const;

    public:
        BezierCurve& operator=(const BezierCurve &) = default;

        [[nodiscard]] Vector3d evaluate(float) const;
        [[nodiscard]] Vector3d tangentAt(float) const;
        [[nodiscard]] Vector3d accelerationAt(float) const;
        [[nodiscard]] Vector3d normalAt(float) const;

        [[nodiscard]] std::pair<BezierCurve, BezierCurve> split(float) const;

        [[nodiscard]] BezierCurve derivative() const;

        [[nodiscard]] Frame getFrenetFrame(float) const;
        [[nodiscard]] Frame getRMF(float, int steps = 100) const;

        [[nodiscard]] float length() const;

        Vector3d& operator[](int);
        const Vector3d& operator[](int) const;

        [[nodiscard]] int getDegree() const;

        [[nodiscard]] std::vector<Vector3d> getPoints() const;
        void setPoints(const std::vector<Vector3d> &);

        ~BezierCurve() = default;
    };
}
