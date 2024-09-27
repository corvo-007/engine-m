#pragma once

#include "core.h"
#include "vector/vector3d.h"

namespace MathEngine {

    class MATH_ENGINE_API Matrix {
    private:
        float matrix[3][3];

    public:
        Matrix();
        Matrix(const float, const float, const float, const float, const float, const float, const float, const float, const float);
        Matrix(const float [3][3]);
        Matrix(const Matrix &);

    private:
        void copy(const float [3][3]);
        float determinant() const;

    public:
        Matrix& operator=(const Matrix &);

        float* operator[](const int);
        const float* operator[](const int) const;

        Matrix operator+(const Matrix &) const;
        Matrix& operator+=(const Matrix &);

        Matrix operator-(const Matrix &) const;
        Matrix& operator-=(const Matrix &);

        Matrix operator*(const float) const;
        Matrix& operator*=(const float);

        Matrix operator/(float) const;
        Matrix& operator/=(float);

        Matrix operator*(const Matrix &) const;
        Matrix& operator*=(const Matrix &);

        Vector3d operator*(const Vector3d &) const;

        bool operator==(const Matrix &) const;
        bool operator!=(const Matrix &) const;

        bool getInverse(Matrix &) const;
        bool inverse();

        Matrix getTranspose() const;
        Matrix& transpose();

        static Matrix identity();

        ~Matrix() = default;
    };
}
