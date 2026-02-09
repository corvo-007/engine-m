#include "engine-m/matrix/matrix.h"

#include <cassert>

#include "engine-m/utils.h"

namespace EngineM {

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols>::Matrix(std::initializer_list<T> list) {
        assert(list.size() == rows * cols);

        auto it = list.begin();

        int i = 0;
        while (it != list.end()) {
            matrix[i / cols][i % cols] = *it++;
            i++;
        }
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols>::Matrix(const T matrix[rows][cols]) {
        copy(matrix);
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols>::Matrix(const Matrix &mat) {
        copy(mat.matrix);
    }

    template <typename T, unsigned int rows, unsigned int cols>
    void Matrix<T, rows, cols>::copy(const T matrix[rows][cols]) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                this -> matrix[i][j] = matrix[i][j];
            }
        }
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator=(const Matrix &mat) {
        if (this == &mat) {
            return *this;
        }
        copy(mat.matrix);
        return *this;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    T* Matrix<T, rows, cols>::operator[](const uint32_t i) {
        return matrix[i];
    }

    template <typename T, unsigned int rows, unsigned int cols>
    const T* Matrix<T, rows, cols>::operator[](const uint32_t i) const {
        return matrix[i];
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols> Matrix<T, rows, cols>::operator+(const Matrix &mat) const {
        Matrix out;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                out[i][j] = matrix[i][j] + mat[i][j];
            }
        }
        return out;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator+=(const Matrix &mat) {
        *this = *this + mat;
        return *this;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols> Matrix<T, rows, cols>::operator-(const Matrix &mat) const {
        Matrix out;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                out[i][j] = matrix[i][j] - mat[i][j];
            }
        }
        return out;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator-=(const Matrix &mat) {
        *this = *this - mat;
        return *this;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols> Matrix<T, rows, cols>::operator*(const T k) const {
        Matrix out;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                out[i][j] = matrix[i][j] * k;
            }
        }
        return out;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator*=(const T k) {
        *this = *this * k;
        return *this;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols> Matrix<T, rows, cols>::operator/(T k) const {
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

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator/=(T k) {
        *this = *this / k;
        return *this;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols> Matrix<T, rows, cols>::operator*(const Matrix &mat) const requires (rows == cols) {
        Matrix out;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                out[i][j] = 0.0f;
                for (int k = 0; k < cols; k++) {
                    out[i][j] += matrix[i][k] * mat[k][j];
                }
            }
        }
        return out;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator*=(const Matrix &mat) requires (rows == cols) {
        *this = *this * mat;
        return *this;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Vector<T, rows> Matrix<T, rows, cols>::operator*(const Vector<T, cols> &vec) const {
        Vector<T, cols> out;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                out[i] += matrix[i][j] * vec[j];
            }
        }
        return out;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    bool Matrix<T, rows, cols>::operator==(const Matrix &mat) const {
        for (uint32_t i = 0; i < rows; i++) {
            for (uint32_t j = 0; j < cols; j++) {
                if (!equals(matrix[i][j], mat[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    bool Matrix<T, rows, cols>::operator!=(const Matrix &mat) const {
        return !(*this == mat);
    }

    template <typename T, unsigned int rows, unsigned int cols>
    T Matrix<T, rows, cols>::determinant() const requires (rows == cols && rows == 1) {
        return matrix[0][0];
    }

    template <typename T, unsigned int rows, unsigned int cols>
    T Matrix<T, rows, cols>::determinant() const requires (rows == cols && rows == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }


    template <typename T, unsigned int rows, unsigned int cols>
    T Matrix<T, rows, cols>::determinant() const requires (rows == cols && rows > 2) {
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

    template <typename T, unsigned int rows, unsigned int cols>
    bool Matrix<T, rows, cols>::getInverse(Matrix &mat) const {
        static_assert(rows == cols, "Only square matrices can be inverted.");

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

    template <typename T, unsigned int rows, unsigned int cols>
    T Matrix<T, rows, cols>::cofactor(int p, int q) const {
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

    template <typename T, unsigned int rows, unsigned int cols>
    bool Matrix<T, rows, cols>::inverse() {
        Matrix mat;
        const bool i = getInverse(mat);
        *this = mat;
        return i;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols> Matrix<T, rows, cols>::getTranspose() const {
        Matrix m;

        for (uint32_t i = 0; i < rows; i++) {
            for (uint32_t j = 0; j < cols; j++) {
                m[j][i] = matrix[i][j];
            }
        }
        return m;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols>& Matrix<T, rows, cols>::transpose() {
        *this = getTranspose();
        return *this;
    }

    template <typename T, unsigned int rows, unsigned int cols>
    Matrix<T, rows, cols> Matrix<T, rows, cols>::identity() requires (rows == cols) {
        Matrix out;
        for (int i = 0; i < rows; i++) {
            out[i][i] = 1;
        }
        return out;
    }

    template class Matrix<int, 3, 3>;
    template class Matrix<int, 4, 4>;

    template class Matrix<float, 3, 3>;
    template class Matrix<float, 4, 4>;

    template class Matrix<double, 3, 3>;
    template class Matrix<double, 4, 4>;
}
