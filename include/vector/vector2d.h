#pragma once

#include "core.h"
#include "vector.h"
#include "vector3d.h"

namespace MathEngine {

    class MATH_ENGINE_API Vector2d : public Vector<Vector2d> {
    public:
        float x {};
        float y {};

        Vector2d() = default;
        Vector2d(float, float);
        Vector2d(const Vector2d &) = default;

        Vector2d& operator=(const Vector2d &) = default;

        Vector2d operator+(const Vector2d &) const override;
        Vector2d& operator+=(const Vector2d &) override;

        Vector2d operator-(const Vector2d &) const override;
        Vector2d& operator-=(const Vector2d &) override;

        Vector2d operator*(float) const override;
        Vector2d& operator*=(float) override;

        Vector2d operator/(float) const override;
        Vector2d& operator/=(float) override;

        Vector2d operator-() const override;

        [[nodiscard]] float dot(const Vector2d &) const override;
        float operator*(const Vector2d &) const override;

        [[nodiscard]] Vector3d cross(const Vector2d &) const override;
        Vector3d operator^(const Vector2d &) const override;

        bool operator==(const Vector2d &) const override;
        bool operator!=(const Vector2d &) const override;

        [[nodiscard]] float magnitude() const override;

        void normalise() override;

        [[nodiscard]] Vector2d rotate(float) const;
        [[nodiscard]] Vector2d rotateRad(float) const;

        ~Vector2d() override = default;
    };
}