#pragma once

#include "core.h"
#include "vector/vector3d.h"

namespace MathEngine {
    
    class MATH_ENGINE_API Quaternion {
    public:
        float a {};
        Vector3d v;

        Quaternion() = default;
        Quaternion(float, const Vector3d &);
        Quaternion(const Quaternion &) = default;

        Quaternion& operator=(const Quaternion &) = default;

        Quaternion operator+(const Quaternion &) const;
        Quaternion& operator+=(const Quaternion &);

        Quaternion operator-(const Quaternion &) const;
        Quaternion& operator-=(const Quaternion &);

        Quaternion operator*(const Quaternion &) const;
        Quaternion& operator*=(const Quaternion &);

        Quaternion operator*(float) const;
        Quaternion& operator*=(float);

        Quaternion operator/(float) const;
        Quaternion& operator/=(float);

        bool operator==(const Quaternion &) const;
        bool operator!=(const Quaternion &) const;

        [[nodiscard]] float norm() const;
        void normalise();

        [[nodiscard]] Quaternion conjugate() const;
        [[nodiscard]] Quaternion inverse() const;

        ~Quaternion() = default;
    };
}
