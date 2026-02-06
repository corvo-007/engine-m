#pragma once

#include "engine-m/core.h"

namespace EngineM {

    class Quaternion;

    template <typename T>
    class ENGINE_M_API Vector3d {
    public:
        union {
            T data[3];
            struct {
                T x, y, z;
            };
        };

        Vector3d();
        Vector3d(T, T, T);
        Vector3d(const Vector3d &) = default;

        Vector3d& operator=(const Vector3d &) = default;

        T& operator[](int i);
        const T& operator[](int i) const;

        Vector3d operator+(const Vector3d &) const;
        Vector3d& operator+=(const Vector3d &);

        Vector3d operator-(const Vector3d &) const;
        Vector3d& operator-=(const Vector3d &);

        Vector3d operator*(T) const;
        Vector3d& operator*=(T);

        Vector3d operator/(T) const;
        Vector3d& operator/=(T);

        Vector3d operator-() const;

        [[nodiscard]] T dot(const Vector3d &) const;
        T operator*(const Vector3d &) const;

        [[nodiscard]] Vector3d cross(const Vector3d &) const;
        [[nodiscard]] Vector3d operator^(const Vector3d &) const;

        Vector3d& operator^=(const Vector3d &);

        bool operator==(const Vector3d &) const;
        bool operator!=(const Vector3d &) const;

        [[nodiscard]] float magnitude() const;

        void normalise();

        [[nodiscard]] Vector3d<float> rotate(float, const Vector3d &) const;
        [[nodiscard]] Vector3d<float> rotateRad(float, const Vector3d &) const;
        [[nodiscard]] Vector3d<float> rotate(const Quaternion &) const;

        ~Vector3d() = default;
    };

    using vec3 = Vector3d<int>;
    using vec3f = Vector3d<float>;
}