#include "engine-m/splines/spline.h"

#include "engine-m/constants.h"
#include "engine-m/utils.h"

namespace EngineM {
    Spline::Spline(const std::vector<Vector3d> &points): points(points) {

    }

    float Spline::legendreGaussQuadratureLength() const {
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

    Frame Spline::getFrenetFrame(float t) const {
        const Vector3d origin = evaluateAt(t);
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

    Frame Spline::getRMF(float t, const int steps) const {
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
            currentFrame.origin = evaluateAt(curr_t);
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

    float Spline::length() const {
        return legendreGaussQuadratureLength();
    }
}
