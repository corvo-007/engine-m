#pragma once

#include <cstdint>
#include <initializer_list>

#include "engine-m/core.h"
#include "engine-m/vector/vector.h"
#include "engine-m/utils.h"

namespace EngineM {

    template <typename T, unsigned int rows, unsigned int cols>
    class ENGINE_M_API Matrix {
        T matrix[rows][cols] {};

    public:
        Matrix() = default;

        explicit Matrix(std::initializer_list<T> list) {
            assert(list.size() == rows * cols);

            auto it = list.begin();

            int i = 0;
            while (it != list.end()) {
                matrix[i / cols][i % cols] = *it++;
                i++;
            }
        }

        explicit Matrix(const T matrix[rows][cols]) {
            copy(matrix);
        }

        Matrix(const Matrix &mat) {
            copy(mat.matrix);
        }

    private:
        void copy(const T matrix[rows][cols]) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    this -> matrix[i][j] = matrix[i][j];
                }
            }
        }

    public:
        Matrix& operator=(const Matrix &mat) {
            if (this == &mat) {
                return *this;
            }
            copy(mat.matrix);
            return *this;
        }

        T* operator[](uint32_t i) {
            return matrix[i];
        }

        const T* operator[](uint32_t i) const {
            return matrix[i];
        }

        Matrix operator+(const Matrix & mat) const {
            Matrix out;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    out[i][j] = matrix[i][j] + mat[i][j];
                }
            }
            return out;
        }

        Matrix& operator+=(const Matrix &mat) {
            *this = *this + mat;
            return *this;
        }

        Matrix operator-(const Matrix &mat) const {
            Matrix out;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    out[i][j] = matrix[i][j] - mat[i][j];
                }
            }
            return out;
        }

        Matrix& operator-=(const Matrix &mat) {
            *this = *this - mat;
            return *this;
        }

        Matrix operator*(T k) const {
            Matrix out;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    out[i][j] = matrix[i][j] * k;
                }
            }
            return out;
        }

        Matrix& operator*=(T k) {
            *this = *this * k;
            return *this;
        }

        Matrix operator/(T k) const {
            if (k == 0) {
                return Matrix();
            }
            Matrix out;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    out[i][j] = matrix[i][j] / k;
                }
            }
            return out;
        }

        Matrix& operator/=(T k) {
            *this = *this / k;
            return *this;
        }

        template <unsigned int ncols>
        Matrix<T, rows, ncols> operator*(const Matrix<T, cols, ncols> &mat) const {
            Matrix<T, rows, ncols> out;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < ncols; j++) {
                    out[i][j] = 0.0f;
                    for (int k = 0; k < cols; k++) {
                        out[i][j] += matrix[i][k] * mat[k][j];
                    }
                }
            }
            return out;
        }

        Matrix& operator*=(const Matrix<T, cols, cols> &mat) {
            *this = *this * mat;
            return *this;
        }

        Vector<T, rows> operator*(const Vector<T, cols> &vec) const {
            Vector<T, rows> out;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    out[i] += matrix[i][j] * vec[j];
                }
            }
            return out;
        }

        bool operator==(const Matrix &mat) const {
            for (uint32_t i = 0; i < rows; i++) {
                for (uint32_t j = 0; j < cols; j++) {
                    if (!equals(matrix[i][j], mat[i][j])) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool operator!=(const Matrix &mat) const {
            return !(*this == mat);
        }

        [[nodiscard]] T determinant() const requires (rows == cols && rows == 1) {
            return matrix[0][0];
        }

        [[nodiscard]] T determinant() const requires (rows == cols && rows == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }

        [[nodiscard]] T determinant() const requires (rows == cols && rows > 2) {
            T det = 0;
            int sign = 1;

            for (unsigned int f = 0; f < cols; f++) {
                Matrix<T, rows - 1, cols - 1> minor;

                for (unsigned int i = 1; i < rows; i++) {
                    unsigned int minor_col = 0;
                    for (unsigned int j = 0; j < cols; j++) {
                        if (j == f) continue;
                        minor[i - 1][minor_col] = matrix[i][j];
                        minor_col++;
                    }
                }

                det += sign * matrix[0][f] * minor.determinant();
                sign = -sign;
            }
            return det;
        }

        [[nodiscard]] T cofactor(int p, int q) const requires (rows == cols) {
            Matrix<T, rows - 1, cols - 1> minor;
            unsigned int rowIdx = 0;
            unsigned int colIdx = 0;

            for (unsigned int i = 0; i < rows; i++) {
                if (i == p) continue;
                colIdx = 0;
                for (unsigned int j = 0; j < cols; j++) {
                    if (j == q) continue;
                    minor[rowIdx][colIdx] = matrix[i][j];
                    colIdx++;
                }
                rowIdx++;
            }

            T sign = ((p + q) % 2 == 0) ? 1 : -1;
            return sign * minor.determinant();
        }

        bool getInverse(Matrix &mat) const requires (rows == cols) {
            T det = determinant();
            if (det == 0) {
                return false;
            }

            if constexpr (rows == 1) {
                mat[0][0] = 1 / det;
                return true;
            } else {
                T invDet = static_cast<T>(1) / det;

                for (unsigned int i = 0; i < rows; i++) {
                    for (unsigned int j = 0; j < cols; j++) {
                        // Get the cofactor of matrix[i][j]
                        // Note the swap of indices (j, i) to perform the Transpose (Adjugate)
                        mat[j][i] = cofactor(i, j) * invDet;
                    }
                }
                return true;
            }
        }

        bool inverse() requires (rows == cols) {
            Matrix mat;
            const bool i = getInverse(mat);
            *this = mat;
            return i;
        }

        [[nodiscard]] Matrix getTranspose() const {
            Matrix m;

            for (uint32_t i = 0; i < rows; i++) {
                for (uint32_t j = 0; j < cols; j++) {
                    m[j][i] = matrix[i][j];
                }
            }
            return m;
        }

        Matrix& transpose() {
            *this = getTranspose();
            return *this;
        }

        static Matrix identity() requires (rows == cols) {
            Matrix out;
            for (int i = 0; i < rows; i++) {
                out[i][i] = 1;
            }
            return out;
        }

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
