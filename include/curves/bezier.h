#pragma once

#include <vector>

#include "core.h"
#include "curve.h"
#include "vector/vector3d.h"
#include "frame.h"

namespace EngineM {

    class ENGINE_M_API BezierCurve : public Curve {
        int degree;
        std::vector<Vector3d> points;

    public:
        BezierCurve() = delete;
        explicit BezierCurve(int);
        BezierCurve(int, const std::vector<Vector3d> &);
        BezierCurve(const BezierCurve &) = default;

    private:
        [[nodiscard]] Vector3d deCasteljau(float) const;

        [[nodiscard]] std::pair<std::unique_ptr<BezierCurve>, std::unique_ptr<BezierCurve>> deCasteljauSplit(float) const;

        [[nodiscard]] float legendreGaussQuadratureLength() const;

    public:
        BezierCurve& operator=(const BezierCurve &) = default;

        [[nodiscard]] Vector3d evaluate(float) const override;
        [[nodiscard]] Vector3d tangentAt(float) const override;
        [[nodiscard]] Vector3d accelerationAt(float) const override;
        [[nodiscard]] Vector3d normalAt(float) const override;

        [[nodiscard]] std::pair<std::unique_ptr<Curve>, std::unique_ptr<Curve>> split(float) const override;

        [[nodiscard]] std::unique_ptr<Curve> derivative() const;

        [[nodiscard]] Frame getFrenetFrame(float) const override;
        [[nodiscard]] Frame getRMF(float, int) const override;

        [[nodiscard]] float length() const override;

        Vector3d& operator[](int);
        const Vector3d& operator[](int) const;

        [[nodiscard]] int getDegree() const;

        [[nodiscard]] std::vector<Vector3d> getPoints() const;
        void setPoints(const std::vector<Vector3d> &);

        ~BezierCurve() override = default;
    };
}
