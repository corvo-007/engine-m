#pragma once

namespace MathEngine {

    class Vector3d;

    template <typename T>
    class Vector {
    public:
        virtual T& operator=(const T &) = 0;

        virtual T operator+(const T &) const = 0;
        virtual T& operator+=(const T &) = 0;

        virtual T operator-(const T &) const = 0;
        virtual T& operator-=(const T &) = 0;

        virtual T operator*(const float) const = 0;
        virtual T& operator*=(const float) = 0;

        virtual T operator/(const float) const = 0;
        virtual T& operator/=(const float) = 0;

        virtual float dot(const T &) const = 0;
        virtual float operator*(const T &) const = 0;

        virtual Vector3d cross(const T &) const = 0;
        virtual Vector3d operator^(const T &) const = 0;

        virtual bool operator==(const T &) const;

        virtual float magnitude() const = 0;
        virtual float operator+() const = 0;

        virtual void normalise() = 0;

        virtual ~Vector() = default;
    };
}