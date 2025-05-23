#include "engine-m/curves/bezier.h"

#include <cmath>
#include <stdexcept>

#include "engine-m/constants.h"
#include "engine-m/utils.h"

namespace EngineM {

    BezierCurve::BezierCurve(const int degree): degree(degree), points(degree + 1) {

    }

    BezierCurve::BezierCurve(const int degree, const std::vector<Vector3d> &points): degree(degree), points(points) {
        if (points.size() != degree + 1) {
            throw std::invalid_argument("Number of control points must be equal to degree + 1");
        }
    }

    Vector3d BezierCurve::deCasteljau(const float t) const {
        std::vector<Vector3d> temp = points;
        for (int i = 1; i < points.size(); i++) {
            for (int j = 0; j < points.size() - i; j++) {
                temp[j] = lerp(temp[j], temp[j + 1], t);
            }
        }
        return temp[0];
    }

    std::pair<std::unique_ptr<BezierCurve>, std::unique_ptr<BezierCurve>> BezierCurve::deCasteljauSplit(const float t) const {
        std::vector<std::vector<Vector3d>> temp(points.size());
        temp[0] = points;

        for (int i = 0; i < temp.size() - 1; i++) {
            for (int j = 0; j < temp[i].size() - 1; j++) {
                temp[i + 1].push_back(lerp(temp[i][j], temp[i][j + 1], t));
            }
        }

        auto *first = new BezierCurve(degree);
        auto *second = new BezierCurve(degree);

        for (int i = 0; i < temp.size(); i++) {
            (*first)[i] = temp[i][0];
            const size_t j = temp.size() - i - 1;
            (*second)[i] = temp[j][temp[j].size() - 1];
        }

        return { std::unique_ptr<BezierCurve>(first), std::unique_ptr<BezierCurve>(second) };
    }

    float BezierCurve::legendreGaussQuadratureLength() const {
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

    Vector3d BezierCurve::evaluate(float t) const {
        t = clamp(t, 0.f, 1.f);
        if (t == 0) {
            return points[0];
        }
        if (t == 1) {
            return points[points.size() - 1];
        }

        Vector3d result;

        float pow_t = 1;
        float pow_1_minus_t = std::pow(1 - t, static_cast<float>(degree));
        const float k = 1.0f / (1 - t);

        for (int i = 0; i < points.size(); i++) {
            result += points[i] * binomialCoefficient(degree, i) * pow_t * pow_1_minus_t;
            pow_t *= t;
            pow_1_minus_t *= k;
        }

        return result;
    }

    Vector3d BezierCurve::tangentAt(const float t) const {
        return (degree == 1) ? points[1] - points[0] : derivative() -> evaluate(t);
    }

    Vector3d BezierCurve::accelerationAt(const float t) const {
        return (degree == 1) ? Vector3d(0, 0, 0) : derivative() -> tangentAt(t);
    }

    Vector3d BezierCurve::normalAt(const float t) const {
        const Frame rmf = getRMF(t, 100);
        return rmf.normal;
    }

    std::pair<std::unique_ptr<Curve>, std::unique_ptr<Curve>> BezierCurve::split(const float t) const {
        return deCasteljauSplit(t);
    }

    std::unique_ptr<Curve> BezierCurve::derivative() const {
        std::vector<Vector3d> temp(points.size() - 1);

        for (int i = 0; i < points.size() - 1; i++) {
            temp[i] = (points[i + 1] - points[i]) * static_cast<float>(degree);
        }

        return std::make_unique<BezierCurve>(degree - 1, temp);
    }

    Frame BezierCurve::getFrenetFrame(const float t) const {
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

    Frame BezierCurve::getRMF(float t, const int steps) const {
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

    float BezierCurve::length() const {
        return legendreGaussQuadratureLength();
    }

    Vector3d& BezierCurve::operator[](const int i) {
        return points[i];
    }

    const Vector3d& BezierCurve::operator[](const int i) const {
        return points[i];
    }

    int BezierCurve::getDegree() const {
        return degree;
    }

    std::vector<Vector3d> BezierCurve::getPoints() const {
        return points;
    }

    void BezierCurve::setPoints(const std::vector<Vector3d> &points) {
        if (points.size() != degree + 1) {
            throw std::invalid_argument("Number of control points must be equal to degree + 1");
        }
        this -> points = points;
    }
}
