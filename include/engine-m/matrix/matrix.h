#pragma once

#include <cstdint>

#include "engine-m/core.h"
#include "engine-m/vector/vector3d.h"

namespace EngineM {

    class ENGINE_M_API Matrix {
        alignas(32) float matrix[3][3] {};

    public:
        Matrix() = default;
        Matrix(float, float, float, float, float, float, float, float, float);
        explicit Matrix(const float [3][3]);
        Matrix(const Matrix &);

    private:
        using MatOp = void (*)(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        using MulKOp = void (*)(const float (&a)[3][3], float k, float (&out)[3][3]);

        static MatOp matrix_add_ptr;
        static MatOp matrix_sub_ptr;
        static MulKOp matrix_mul_by_k_ptr;
        static MatOp matrix_mul_ptr;

        static void detection_and_dispatch();
        static void add_dispatch(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        static void sub_dispatch(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        static void mul_by_k_dispatch(const float (&a)[3][3], float k, float (&out)[3][3]);
        static void mul_dispatch(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);

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

        vec3f operator*(const vec3f &) const;

        bool operator==(const Matrix &) const;
        bool operator!=(const Matrix &) const;

        bool getInverse(Matrix &) const;
        bool inverse();

        [[nodiscard]] Matrix getTranspose() const;
        Matrix& transpose();

        static Matrix identity();

        ~Matrix() = default;
    };

    using mat3 = Matrix;
}
