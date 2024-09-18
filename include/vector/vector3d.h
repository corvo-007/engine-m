#pragma once

#include "core.h"
#include "vector.h"

namespace MathEngine {

    class Quaternion;

    class MATH_ENGINE_API Vector3d : public Vector<Vector3d> {
    public:
        float x;
        float y;
        float z;

        Vector3d();
        Vector3d(float, float, float);
        Vector3d(const Vector3d &);

        virtual Vector3d &operator=(const Vector3d &) override;

        virtual Vector3d operator+(const Vector3d &) const override;
        virtual Vector3d& operator+=(const Vector3d &) override;

        virtual Vector3d operator-(const Vector3d &) const override;
        virtual Vector3d& operator-=(const Vector3d &) override;

        virtual Vector3d operator*(const float) const override;
        virtual Vector3d& operator*=(const float) override;

        virtual Vector3d operator/(const float) const override;
        virtual Vector3d& operator/=(const float) override;

        virtual float dot(const Vector3d &) const override;
        virtual float operator*(const Vector3d &) const override;

        virtual Vector3d cross(const Vector3d &) const override;
        virtual Vector3d operator^(const Vector3d &) const override;

        Vector3d& operator^=(const Vector3d &);

        virtual bool operator==(const Vector3d &) const override;
        virtual bool operator!=(const Vector3d &) const override;

        virtual float magnitude() const override;
        virtual float operator+() const override;

        virtual void normalise() override;

        Vector3d rotate(const float, const Vector3d &) const;
        Vector3d rotateRad(const float, const Vector3d &) const;
        Vector3d rotate(const Quaternion &) const;

        ~Vector3d() = default;
    };
}