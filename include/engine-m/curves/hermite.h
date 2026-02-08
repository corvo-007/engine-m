#pragma once

#include "engine-m/core.h"
#include "curve.h"
#include <vector>
#include "engine-m/vector/vector.h"

namespace EngineM {

    class ENGINE_M_API HermiteCurve : public Curve {
        vec3f p1;
        vec3f p2;
        vec3f v1;
        vec3f v2;

    public:
        HermiteCurve() = default;
        HermiteCurve(const vec3f &, const vec3f &, const vec3f &, const vec3f &);
        HermiteCurve(const HermiteCurve &) = default;

    private:
        [[nodiscard]] float legendreGaussQuadratureLength() const;

    public:
        HermiteCurve& operator=(const HermiteCurve &) = default;

        [[nodiscard]] vec3f evaluate(float) const override;
        [[nodiscard]] vec3f tangentAt(float) const override;
        [[nodiscard]] vec3f accelerationAt(float) const override;
        [[nodiscard]] vec3f normalAt(float) const override;

        [[nodiscard]] std::pair<std::unique_ptr<Curve>, std::unique_ptr<Curve>> split(float) const override;

        [[nodiscard]] Frame getFrenetFrame(float) const override;
        [[nodiscard]] Frame getRMF(float, int) const override;

        [[nodiscard]] float length() const override;

        [[nodiscard]] std::pair<vec3f, vec3f> getPoints() const;
        [[nodiscard]] vec3f getStart() const;
        [[nodiscard]] vec3f getEnd() const;

        void setPoints(const vec3f &, const vec3f &);
        void setStart(const vec3f &);
        void setEnd(const vec3f &);

        [[nodiscard]] std::pair<vec3f, vec3f> getTangents() const;
        [[nodiscard]] vec3f getStartTangent() const;
        [[nodiscard]] vec3f getEndTangent() const;

        void setTangents(const vec3f &, const vec3f &);
        void setStartTangent(const vec3f &);
        void setEndTangent(const vec3f &);
    };
}
