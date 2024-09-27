#pragma once

#include "core.h"
#include "vector/vector3d.h"

namespace MathEngine {

    class MATH_ENGINE_API Matrix {
        float matrix[3][3] {};

    public:
        Matrix() = default;
        Matrix(float, float, float, float, float, float, float, float, float);
        explicit Matrix(const float [3][3]);
        Matrix(const Matrix &);

    private:
        void copy(const float [3][3]);
        [[nodiscard]] float determinant() const;

    public:
        Matrix& operator=(const Matrix &);

        float* operator[](int);
        const float* operator[](int) const;

        Matrix operator+(const Matrix &) const;
        Matrix& operator+=(const Matrix &);

        Matrix operator-(const Matrix &) const;
        Matrix& operator-=(const Matrix &);

        Matrix operator*(float) const;
        Matrix& operator*=(float);

        Matrix operator/(float) const;
        Matrix& operator/=(float);

        Matrix operator*(const Matrix &) const;
        Matrix& operator*=(const Matrix &);

        Vector3d operator*(const Vector3d &) const;

        bool operator==(const Matrix &) const;
        bool operator!=(const Matrix &) const;

        bool getInverse(Matrix &) const;
        bool inverse();

        [[nodiscard]] Matrix getTranspose() const;
        Matrix& transpose();

        static Matrix identity();

        ~Matrix() = default;
    };
}
