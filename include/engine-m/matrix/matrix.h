#pragma once

#include <cstdint>

#include "engine-m/core.h"
#include "engine-m/simd.h"
#include "engine-m/vector/vector3d.h"

namespace EngineM {

    class ENGINE_M_API Matrix {
        alignas(MATRIX_ALIGNMENT) float matrix[3][3] {};

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

        float* operator[](uint32_t);
        const float* operator[](uint32_t) const;

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
