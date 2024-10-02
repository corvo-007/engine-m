#pragma once

#include "vector/vector3d.h"

namespace MathEngine {

    class MATH_ENGINE_API Frame {
    public:
        Vector3d origin;
        Vector3d tangent;
        Vector3d normal;
        Vector3d rotationAxis;

        Frame() = default;
        Frame(const Vector3d &, const Vector3d &, const Vector3d &, const Vector3d &);
        Frame(const Frame &) = default;

        Frame& operator=(const Frame &) = default;

        ~Frame() = default;
    };
}