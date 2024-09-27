#pragma once

#include "core.h"
#include "vector.h"

namespace MathEngine {

    class Quaternion;

    class MATH_ENGINE_API Vector3d : public Vector<Vector3d> {
    public:
        float x {};
        float y {};
        float z {};

        Vector3d() = default;
        Vector3d(float, float, float);
        Vector3d(const Vector3d &) = default;

        Vector3d &operator=(const Vector3d &) = default;

        Vector3d operator+(const Vector3d &) const override;
        Vector3d& operator+=(const Vector3d &) override;

        Vector3d operator-(const Vector3d &) const override;
        Vector3d& operator-=(const Vector3d &) override;

        Vector3d operator*(float) const override;
        Vector3d& operator*=(float) override;

        Vector3d operator/(float) const override;
        Vector3d& operator/=(float) override;

        Vector3d operator-() const override;

        [[nodiscard]] float dot(const Vector3d &) const override;
        float operator*(const Vector3d &) const override;

        [[nodiscard]] Vector3d cross(const Vector3d &) const override;
        Vector3d operator^(const Vector3d &) const override;

        Vector3d& operator^=(const Vector3d &);

        bool operator==(const Vector3d &) const override;
        bool operator!=(const Vector3d &) const override;

        [[nodiscard]] float magnitude() const override;

        void normalise() override;

        [[nodiscard]] Vector3d rotate(float, const Vector3d &) const;
        [[nodiscard]] Vector3d rotateRad(float, const Vector3d &) const;
        [[nodiscard]] Vector3d rotate(const Quaternion &) const;

        ~Vector3d() override = default;
    };
}