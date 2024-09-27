#pragma once

#include "core.h"

namespace MathEngine {

    class Vector3d;

    template <typename T>
    class MATH_ENGINE_API Vector {
    public:
        virtual T operator+(const T &) const = 0;
        virtual T& operator+=(const T &) = 0;

        virtual T operator-(const T &) const = 0;
        virtual T& operator-=(const T &) = 0;

        virtual T operator*(float) const = 0;
        virtual T& operator*=(float) = 0;

        virtual T operator/(float) const = 0;
        virtual T& operator/=(float) = 0;

        virtual T operator-() const = 0;

        virtual float dot(const T &) const = 0;
        virtual float operator*(const T &) const = 0;

        virtual Vector3d cross(const T &) const = 0;
        virtual Vector3d operator^(const T &) const = 0;

        virtual bool operator==(const T &) const = 0;
        virtual bool operator!=(const T &) const = 0;

        [[nodiscard]] virtual float magnitude() const = 0;

        virtual void normalise() = 0;

        virtual ~Vector() = default;
    };
}