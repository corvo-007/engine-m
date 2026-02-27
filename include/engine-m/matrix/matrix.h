#pragma once

#include <cstdint>
#include <initializer_list>

#include "engine-m/core.h"
#include "engine-m/vector/vector.h"

namespace EngineM {

    template <typename T, unsigned int rows, unsigned int cols>
    class ENGINE_M_API Matrix {
        T matrix[rows][cols] {};

    public:
        Matrix() = default;

        explicit Matrix(std::initializer_list<T> list);

        explicit Matrix(const T [rows][cols]);
        Matrix(const Matrix &);

    private:
        void copy(const T [rows][cols]);

    public:
        Matrix& operator=(const Matrix &);

        T* operator[](uint32_t);
        const T* operator[](uint32_t) const;

        Matrix operator+(const Matrix &) const;
        Matrix& operator+=(const Matrix &);

        Matrix operator-(const Matrix &) const;
        Matrix& operator-=(const Matrix &);

        Matrix operator*(T) const;
        Matrix& operator*=(T);

        Matrix operator/(T) const;
        Matrix& operator/=(T);

        Matrix operator*(const Matrix &) const requires (rows == cols);
        Matrix& operator*=(const Matrix &) requires (rows == cols);

        Vector<T, rows> operator*(const Vector<T, cols> &) const;

        bool operator==(const Matrix &) const;
        bool operator!=(const Matrix &) const;

        [[nodiscard]] T determinant() const requires (rows == cols && rows == 1);
        [[nodiscard]] T determinant() const requires (rows == cols && rows == 2);
        [[nodiscard]] T determinant() const requires (rows == cols && rows > 2);

        [[nodiscard]] T cofactor(int p, int q) const requires (rows == cols);

        bool getInverse(Matrix &) const requires (rows == cols);
        bool inverse() requires (rows == cols);

        [[nodiscard]] Matrix getTranspose() const;
        Matrix& transpose();

        static Matrix identity() requires (rows == cols);

        ~Matrix() = default;
    };

    using mat2 = Matrix<int, 2, 2>;
    using mat2x3 = Matrix<int, 2, 3>;
    using mat2x4 = Matrix<int, 2, 4>;

    using mat3x2 = Matrix<int, 3, 2>;
    using mat3 = Matrix<int, 3, 3>;
    using mat3x4 = Matrix<int, 3, 4>;

    using mat4x2 = Matrix<int, 4, 2>;
    using mat4x3 = Matrix<int, 4, 3>;
    using mat4 = Matrix<int, 4, 4>;

    using mat2f = Matrix<float, 2, 2>;
    using mat2x3f = Matrix<float, 2, 3>;
    using mat2x4f = Matrix<float, 2, 4>;

    using mat3x2f = Matrix<float, 3, 2>;
    using mat3f = Matrix<float, 3, 3>;
    using mat3x4f = Matrix<float, 3, 4>;

    using mat4x2f = Matrix<float, 4, 2>;
    using mat4x3f = Matrix<float, 4, 3>;
    using mat4f = Matrix<float, 4, 4>;

    using mat2d = Matrix<double, 2, 2>;
    using mat2x3d = Matrix<double, 2, 3>;
    using mat2x4d = Matrix<double, 2, 4>;

    using mat3x2d = Matrix<double, 3, 2>;
    using mat3d = Matrix<double, 3, 3>;
    using mat3x4d = Matrix<double, 3, 4>;

    using mat4x2d = Matrix<double, 4, 2>;
    using mat4x3d = Matrix<double, 4, 3>;
    using mat4d = Matrix<double, 4, 4>;

}
