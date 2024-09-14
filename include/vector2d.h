#pragma once

#include "vector.h"
#include "vector3d.h"

namespace MathEngine {

    class Vector2d : public Vector<Vector2d> {
    public:
        float x;
        float y;

        Vector2d();
        Vector2d(float, float);
        Vector2d(const Vector2d &);

        virtual Vector2d& operator=(const Vector2d &) override;

        virtual Vector2d operator+(const Vector2d &) const override;
        virtual Vector2d& operator+=(const Vector2d &) override;

        virtual Vector2d operator-(const Vector2d &) const override;
        virtual Vector2d& operator-=(const Vector2d &) override;

        virtual Vector2d operator*(const float) const override;
        virtual Vector2d& operator*=(const float) override;

        virtual Vector2d operator/(const float) const override;
        virtual Vector2d& operator/=(const float) override;

        virtual float dot(const Vector2d &) const override;
        virtual float operator*(const Vector2d &) const override;

        virtual Vector3d cross(const Vector2d &) const override;
        virtual Vector3d operator^(const Vector2d &) const override;

        virtual float magnitude() const override;
        virtual float operator+() const override;

        virtual void normalise() override;

        ~Vector2d() = default;
    };
}