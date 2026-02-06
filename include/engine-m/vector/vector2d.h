#pragma once

#include "engine-m/core.h"

namespace EngineM {

    template <typename T>
    class ENGINE_M_API Vector2d {
    public:
        union {
            T data[2];
            struct {
                T x, y;
            };
        };

        Vector2d();
        Vector2d(T, T);
        Vector2d(const Vector2d &) = default;

        Vector2d& operator=(const Vector2d &) = default;

        T& operator[](int i);
        const T& operator[](int i) const;

        Vector2d operator+(const Vector2d &) const;
        Vector2d& operator+=(const Vector2d &);

        Vector2d operator-(const Vector2d &) const;
        Vector2d& operator-=(const Vector2d &);

        Vector2d operator*(T) const;
        Vector2d& operator*=(T);

        Vector2d operator/(T) const;
        Vector2d& operator/=(T);

        Vector2d operator-() const;

        [[nodiscard]] T dot(const Vector2d &) const;
        T operator*(const Vector2d &) const;

        [[nodiscard]] T cross(const Vector2d &) const;
        [[nodiscard]] T operator^(const Vector2d &) const;

        bool operator==(const Vector2d &) const;
        bool operator!=(const Vector2d &) const;

        [[nodiscard]] float magnitude() const;

        void normalise();

        [[nodiscard]] Vector2d<float> rotate(float) const;
        [[nodiscard]] Vector2d<float> rotateRad(float) const;

        ~Vector2d() = default;
    };

    using vec2 = Vector2d<int>;
    using vec2f = Vector2d<float>;
}