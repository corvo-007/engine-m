#pragma once

#include "engine-m/core.h"
#include "engine-m/vector/vector.h"

namespace EngineM {
    
    class ENGINE_M_API Quaternion {
    public:
        float a {};
        vec3f v;

        Quaternion() = default;
        Quaternion(float, const vec3f &);
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
