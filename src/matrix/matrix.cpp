#include "engine-m/matrix/matrix.h"

#include "engine-m/utils.h"
#include "engine-m/simd.h"
#include "kernels/kernel_declarations.h"

namespace EngineM {

    Matrix::Matrix(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h, const float i): matrix{{a, b, c}, {d, e, f}, {g, h, i}} {

    }

    Matrix::Matrix(const float matrix[3][3]) {
        copy(matrix);
    }

    Matrix::Matrix(const Matrix &mat) {
        copy(mat.matrix);
    }

    Matrix::MatOp Matrix::matrix_add_ptr = add_dispatch;
    Matrix::MatOp Matrix::matrix_sub_ptr = sub_dispatch;
    Matrix::MulKOp Matrix::matrix_mul_by_k_ptr = mul_by_k_dispatch;
    Matrix::MatOp Matrix::matrix_mul_ptr = mul_dispatch;

    void Matrix::detection_and_dispatch() {
        switch (SIMD::get_simd_level()) {
            case SIMD::Level::AVX2:
                matrix_add_ptr = kernels::avx2::matrix_add;
                matrix_sub_ptr = kernels::avx2::matrix_sub;
                matrix_mul_by_k_ptr = kernels::avx2::matrix_mul_by_k;
                matrix_mul_ptr = kernels::avx2::matrix_mul;
                break;
            case SIMD::Level::AVX:
                matrix_add_ptr = kernels::avx::matrix_add;
                matrix_sub_ptr = kernels::avx::matrix_sub;
                matrix_mul_by_k_ptr = kernels::avx::matrix_mul_by_k;
                matrix_mul_ptr = kernels::avx::matrix_mul;
                break;
            case SIMD::Level::SSE2:
                matrix_add_ptr = kernels::sse::matrix_add;
                matrix_sub_ptr = kernels::sse::matrix_sub;
                matrix_mul_by_k_ptr = kernels::sse::matrix_mul_by_k;
                matrix_mul_ptr = kernels::sse::matrix_mul;
                break;
            case SIMD::Level::Scalar:
                matrix_add_ptr = kernels::scalar::matrix_add;
                matrix_sub_ptr = kernels::scalar::matrix_sub;
                matrix_mul_by_k_ptr = kernels::scalar::matrix_mul_by_k;
                matrix_mul_ptr = kernels::scalar::matrix_mul;
        }
    }

    void Matrix::add_dispatch(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]) {
        detection_and_dispatch();
        matrix_add_ptr(a, b, out);
    }

    void Matrix::sub_dispatch(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]) {
        detection_and_dispatch();
        matrix_sub_ptr(a, b, out);
    }

    void Matrix::mul_by_k_dispatch(const float (&a)[3][3], float k, float (&out)[3][3]) {
        detection_and_dispatch();
        matrix_mul_by_k_ptr(a, k, out);
    }

    void Matrix::mul_dispatch(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]) {
        detection_and_dispatch();
        matrix_mul_ptr(a, b, out);
    }

    void Matrix::copy(const float matrix[3][3]) {
        this -> matrix[0][0] = matrix[0][0];
        this -> matrix[0][1] = matrix[0][1];
        this -> matrix[0][2] = matrix[0][2];
        this -> matrix[1][0] = matrix[1][0];
        this -> matrix[1][1] = matrix[1][1];
        this -> matrix[1][2] = matrix[1][2];
        this -> matrix[2][0] = matrix[2][0];
        this -> matrix[2][1] = matrix[2][1];
        this -> matrix[2][2] = matrix[2][2];
    }

    float Matrix::determinant() const {
        return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    }

    Matrix& Matrix::operator=(const Matrix &mat) {
        if (this == &mat) {
            return *this;
        }
        copy(mat.matrix);
        return *this;
    }

    float* Matrix::operator[](const uint32_t i) {
        return matrix[i];
    }

    const float* Matrix::operator[](const uint32_t i) const {
        return matrix[i];
    }

    Matrix Matrix::operator+(const Matrix &mat) const {
        Matrix out;
        matrix_add_ptr(matrix, mat.matrix, out.matrix);
        return out;
    }

    Matrix& Matrix::operator+=(const Matrix &mat) {
        *this = *this + mat;
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &mat) const {
        Matrix out;
        matrix_sub_ptr(matrix, mat.matrix, out.matrix);
        return out;
    }

    Matrix& Matrix::operator-=(const Matrix &mat) {
        *this = *this - mat;
        return *this;
    }

    Matrix Matrix::operator*(const float k) const {
        Matrix out;
        matrix_mul_by_k_ptr(matrix, k, out.matrix);
        return out;
    }

    Matrix& Matrix::operator*=(const float k) {
        *this = *this * k;
        return *this;
    }

    Matrix Matrix::operator/(float k) const {
        k = 1 / k;
        return *this * k;
    }

    Matrix& Matrix::operator/=(float k) {
        k = 1 / k;
        return *this *= k;
    }

    Matrix Matrix::operator*(const Matrix &mat) const {
        Matrix out;
        matrix_mul_ptr(matrix, mat.matrix, out.matrix);
        return out;
    }

    Matrix& Matrix::operator*=(const Matrix &mat) {
        *this = *this * mat;
        return *this;
    }

    Vector3d Matrix::operator*(const Vector3d &vec) const {
	    return {matrix[0][0] * vec.x + matrix[0][1] * vec.y + matrix[0][2] * vec.z, matrix[1][0] * vec.x + matrix[1][1] * vec.y + matrix[1][2] * vec.z, matrix[2][0] * vec.x + matrix[2][1] * vec.y + matrix[2][2] * vec.z};
    }

    bool Matrix::operator==(const Matrix &mat) const {
        for (uint32_t i = 0; i < 3; i++) {
            for (uint32_t j = 0; j < 3; j++) {
                if (!equals(matrix[i][j], mat[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix &mat) const {
        return !(*this == mat);
    }

    bool Matrix::getInverse(Matrix &mat) const {
        const float det = determinant();

        if (det == 0.0) {
            return false;
        }

        const float oneOverDet = 1 / det;

        mat[0][0] = oneOverDet * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]);
        mat[0][1] = -oneOverDet *  (matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
        mat[0][2] = oneOverDet * (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]);
        mat[1][0] = -oneOverDet *  (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
        mat[1][1] = oneOverDet * (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]);
        mat[1][2] = -oneOverDet *  (matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
        mat[2][0] = oneOverDet * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
        mat[2][1] = -oneOverDet *  (matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
        mat[2][2] = oneOverDet * (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);

        return true;
    }

    bool Matrix::inverse() {
        Matrix mat;
        const bool i = getInverse(mat);
        *this = mat;
        return i;
    }

    Matrix Matrix::getTranspose() const {
        Matrix m;

        for (uint32_t i = 0; i < 3; i++) {
            for (uint32_t j = 0; j < 3; j++) {
                m[j][i] = matrix[i][j];
            }
        }
        return m;
    }

    Matrix& Matrix::transpose() {
        *this = getTranspose();
        return *this;
    }

    Matrix Matrix::identity() {
        return {1, 0, 0, 0, 1, 0, 0, 0, 1};
    }
}
