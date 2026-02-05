#pragma once

#include <vector>

#include "engine-m/core.h"
#include "curve.h"
#include "engine-m/vector/vector3d.h"
#include "engine-m/frame.h"

namespace EngineM {

    class ENGINE_M_API BezierCurve : public Curve {
        int degree;
        std::vector<vec3f> points;

    public:
        BezierCurve() = delete;
        explicit BezierCurve(int);
        BezierCurve(int, const std::vector<vec3f> &);
        BezierCurve(const BezierCurve &) = default;

    private:
        [[nodiscard]] vec3f deCasteljau(float) const;

        [[nodiscard]] std::pair<std::unique_ptr<BezierCurve>, std::unique_ptr<BezierCurve>> deCasteljauSplit(float) const;

        [[nodiscard]] float legendreGaussQuadratureLength() const;

    public:
        BezierCurve& operator=(const BezierCurve &) = default;

        [[nodiscard]] vec3f evaluate(float) const override;
        [[nodiscard]] vec3f tangentAt(float) const override;
        [[nodiscard]] vec3f accelerationAt(float) const override;
        [[nodiscard]] vec3f normalAt(float) const override;

        [[nodiscard]] std::pair<std::unique_ptr<Curve>, std::unique_ptr<Curve>> split(float) const override;

        [[nodiscard]] std::unique_ptr<Curve> derivative() const;

        [[nodiscard]] Frame getFrenetFrame(float) const override;
        [[nodiscard]] Frame getRMF(float, int) const override;

        [[nodiscard]] float length() const override;

        vec3f& operator[](int);
        const vec3f& operator[](int) const;

        [[nodiscard]] int getDegree() const;

        [[nodiscard]] std::vector<vec3f> getPoints() const;
        void setPoints(const std::vector<vec3f> &);

        ~BezierCurve() override = default;
    };
}
