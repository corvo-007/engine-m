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

        [[nodiscard]] T cofactor(int p, int q) const;

        bool getInverse(Matrix &) const;
        bool inverse();

        [[nodiscard]] Matrix getTranspose() const;
        Matrix& transpose();

        static Matrix identity() requires (rows == cols);

        ~Matrix() = default;
    };

    using mat3 = Matrix<int, 3, 3>;
    using mat4 = Matrix<int, 4, 4>;

    using mat3f = Matrix<float, 3, 3>;
    using mat4f = Matrix<float, 4, 4>;

    using mat3d = Matrix<double, 3, 3>;
    using mat4d = Matrix<double, 4, 4>;
}
