#include "curves/hermite.h"

#include <iostream>

#include "constants.h"
#include "utils.h"

namespace EngineM {

    HermiteCurve::HermiteCurve(const Vector3d &p1, const Vector3d &p2, const Vector3d &v1, const Vector3d &v2): p1(p1), p2(p2), v1(v1), v2(v2) {

    }

    float HermiteCurve::legendreGaussQuadratureLength() const {
        constexpr float z = 0.5;
        constexpr int n = LEGENDRE_GAUSS_QUADRATURE_WEIGHTS_AND_ABSCISSAE.size();

        float sum = 0;

        for (int i = 0; i < n; i++) {
            const float weight = LEGENDRE_GAUSS_QUADRATURE_WEIGHTS_AND_ABSCISSAE[i][0];
            const float abscissa = LEGENDRE_GAUSS_QUADRATURE_WEIGHTS_AND_ABSCISSAE[i][1];

            const Vector3d tangent = tangentAt(z * abscissa + z);

            sum += weight * tangent.magnitude();
        }
        return z * sum;
    }

    Vector3d HermiteCurve::evaluate(float t) const {
        t = clamp(t, 0.f, 1.f);
        const float t_square = t * t;
        const float t_cube = t * t * t;

        return p1 * (2 * t_cube - 3 * t_square + 1) + v1 * (t_cube - 2 * t_square + t) + p2 * (-2 * t_cube + 3 * t_square) + v2 * (t_cube - t_square);
    }

    Vector3d HermiteCurve::tangentAt(float t) const {
        t = clamp(t, 0.f, 1.f);
        const float t_square = t * t;
        const float temp = 6 * (t_square - t);

        return p1 * temp + v1 * (3 * t_square - 4 * t + 1) - p2 * temp + v2 * (3 * t_square - 2 * t);
    }

    Vector3d HermiteCurve::accelerationAt(float t) const {
        t = clamp(t, 0.f, 1.f);
        const float temp1 = 6 * (2 * t - 1);
        const float temp2 = 6 * t - 2;

        return p1 * temp1 + v1 * (temp2 - 2) - p2 * temp1 + v2 * temp2;
    }

    Vector3d HermiteCurve::normalAt(const float t) const {
        const Frame rmf = getRMF(t, 100);
        return rmf.normal;
    }

    std::pair<std::unique_ptr<Curve>, std::unique_ptr<Curve>> HermiteCurve::split(const float t) const {
        Vector3d pt = evaluate(t);
        Vector3d vt = tangentAt(t);

        std::unique_ptr<Curve> c1 = std::make_unique<HermiteCurve>(p1, pt, v1, vt);
        std::unique_ptr<Curve> c2 = std::make_unique<HermiteCurve>(pt, p2, vt, v2);

        return { std::move(c1), std::move(c2) };
    }

    Frame HermiteCurve::getFrenetFrame(const float t) const {
        const Vector3d origin = evaluate(t);
        Vector3d tangent = tangentAt(t);
        tangent.normalise();
        const Vector3d acceleration = accelerationAt(t);
        const Vector3d temp = tangent + acceleration;
        Vector3d rotationAxis = temp ^ tangent;
        rotationAxis.normalise();
        Vector3d normal = rotationAxis ^ tangent;
        normal.normalise();

        return { origin, tangent, normal, rotationAxis };
    }

    Frame HermiteCurve::getRMF(float t, const int steps) const {
        t = clamp(t, 0.f, 1.f);

        Frame frenetFrame = getFrenetFrame(0);

        if (t == 0) {
            return frenetFrame;
        }

        Frame lastFrame = frenetFrame;

        const float step_size = t / static_cast<float>(steps);
        float curr_t = step_size;

        for (int i = 1; i <= steps; i++) {
            Frame currentFrame;
            currentFrame.origin = evaluate(curr_t);
            currentFrame.tangent = tangentAt(curr_t);
            currentFrame.tangent.normalise();

            Vector3d posDiff = currentFrame.origin - lastFrame.origin;
            float magSquare = posDiff * posDiff;
            const Vector3d rotationAxisRef = lastFrame.rotationAxis - posDiff * 2 / magSquare * (posDiff * lastFrame.rotationAxis);
            const Vector3d tangentRef = lastFrame.tangent - posDiff * 2 / magSquare * (posDiff * lastFrame.tangent);

            posDiff = currentFrame.tangent - tangentRef;
            magSquare = posDiff * posDiff;

            currentFrame.rotationAxis = rotationAxisRef - posDiff * 2 / magSquare * (posDiff * rotationAxisRef);
            currentFrame.normal = currentFrame.rotationAxis ^ currentFrame.tangent;

            lastFrame = currentFrame;
            curr_t += step_size;
        }

        return lastFrame;
    }


    float HermiteCurve::length() const {
        return legendreGaussQuadratureLength();
    }

    std::pair<Vector3d, Vector3d> HermiteCurve::getPoints() const {
        return { p1, p2 };
    }

    Vector3d HermiteCurve::getStart() const {
        return p1;
    }

    Vector3d HermiteCurve::getEnd() const {
        return p2;
    }

    void HermiteCurve::setPoints(const Vector3d &p1, const Vector3d &p2) {
        this -> p1 = p1;
        this -> p2 = p2;
    }

    void HermiteCurve::setStart(const Vector3d &p) {
        p1 = p;
    }

    void HermiteCurve::setEnd(const Vector3d &p) {
        p2 = p;
    }

    std::pair<Vector3d, Vector3d> HermiteCurve::getTangents() const {
        return { v1, v2 };
    }

    Vector3d HermiteCurve::getStartTangent() const {
        return v1;
    }

    Vector3d HermiteCurve::getEndTangent() const {
        return v2;
    }

    void HermiteCurve::setTangents(const Vector3d &v1, const Vector3d &v2) {
        this -> v1 = v1;
        this -> v2 = v2;
    }

    void HermiteCurve::setStartTangent(const Vector3d &v) {
        v1 = v;
    }

    void HermiteCurve::setEndTangent(const Vector3d &v) {
        v2 = v;
    }
}
