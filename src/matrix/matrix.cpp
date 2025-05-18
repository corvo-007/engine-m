#include "engine-m/matrix/matrix.h"

#if defined(USE_AVX2) || defined(USE_SSE2)
#include <immintrin.h>
#endif

#include "engine-m/utils.h"

namespace EngineM {

    Matrix::Matrix(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h, const float i): matrix{{a, b, c}, {d, e, f}, {g, h, i}} {

    }

    Matrix::Matrix(const float matrix[3][3]) {
        copy(matrix);
    }

    Matrix::Matrix(const Matrix &mat) {
        copy(mat.matrix);
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
        Matrix m;

#if defined(USE_AVX2)

        const __m256 first = _mm256_set_ps(matrix[2][1], matrix[2][0], matrix[1][2], matrix[1][1], matrix[1][0], matrix[0][2], matrix[0][1], matrix[0][0]);
        const __m256 second = _mm256_set_ps(mat[2][1], mat[2][0], mat[1][2], mat[1][1], mat[1][0], mat[0][2], mat[0][1], mat[0][0]);
        const __m256 sum = _mm256_add_ps(first, second);

        _mm256_store_ps(&m[0][0], sum);
        m[2][2] = matrix[2][2] + mat[2][2];

#elif defined(USE_SSE2)

        const __m128 first = _mm_set_ps(matrix[1][0], matrix[0][2], matrix[0][1], matrix[0][0]);
        const __m128 second = _mm_set_ps(matrix[2][1], matrix[2][0], matrix[1][2], matrix[1][1]);
        const __m128 third = _mm_set_ps(mat[1][0], mat[0][2], mat[0][1], mat[0][0]);
        const __m128 fourth = _mm_set_ps(mat[2][1], mat[2][0], mat[1][2], mat[1][1]);

        const __m128 sum1 = _mm_add_ps(first, third);
        const __m128 sum2 = _mm_add_ps(second, fourth);

        _mm_store_ps(&m[0][0], sum1);
        _mm_store_ps(&m[1][1], sum2);
        m[2][2] = matrix[2][2] + mat[2][2];

#else

        m[0][0] = matrix[0][0] + mat[0][0];
        m[0][1] = matrix[0][1] + mat[0][1];
        m[0][2] = matrix[0][2] + mat[0][2];
        m[1][0] = matrix[1][0] + mat[1][0];
        m[1][1] = matrix[1][1] + mat[1][1];
        m[1][2] = matrix[1][2] + mat[1][2];
        m[2][0] = matrix[2][0] + mat[2][0];
        m[2][1] = matrix[2][1] + mat[2][1];
        m[2][2] = matrix[2][2] + mat[2][2];

#endif

        return m;
    }

    Matrix& Matrix::operator+=(const Matrix &mat) {
        *this = *this + mat;
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &mat) const {
        Matrix m;

#if defined(USE_AVX2)

        const __m256 first = _mm256_set_ps(matrix[2][1], matrix[2][0], matrix[1][2], matrix[1][1], matrix[1][0], matrix[0][2], matrix[0][1], matrix[0][0]);
        const __m256 second = _mm256_set_ps(mat[2][1], mat[2][0], mat[1][2], mat[1][1], mat[1][0], mat[0][2], mat[0][1], mat[0][0]);
        const __m256 sum = _mm256_sub_ps(first, second);

        _mm256_store_ps(&m[0][0], sum);
        m[2][2] = matrix[2][2] - mat[2][2];

#elif defined(USE_SSE2)

        const __m128 first = _mm_set_ps(matrix[1][0], matrix[0][2], matrix[0][1], matrix[0][0]);
        const __m128 second = _mm_set_ps(matrix[2][1], matrix[2][0], matrix[1][2], matrix[1][1]);
        const __m128 third = _mm_set_ps(mat[1][0], mat[0][2], mat[0][1], mat[0][0]);
        const __m128 fourth = _mm_set_ps(mat[2][1], mat[2][0], mat[1][2], mat[1][1]);

        const __m128 sum1 = _mm_sub_ps(first, third);
        const __m128 sum2 = _mm_sub_ps(second, fourth);

        _mm_store_ps(&m[0][0], sum1);
        _mm_store_ps(&m[1][1], sum2);
        m[2][2] = matrix[2][2] - mat[2][2];

#else

        m[0][0] = matrix[0][0] - mat[0][0];
        m[0][1] = matrix[0][1] - mat[0][1];
        m[0][2] = matrix[0][2] - mat[0][2];
        m[1][0] = matrix[1][0] - mat[1][0];
        m[1][1] = matrix[1][1] - mat[1][1];
        m[1][2] = matrix[1][2] - mat[1][2];
        m[2][0] = matrix[2][0] - mat[2][0];
        m[2][1] = matrix[2][1] - mat[2][1];
        m[2][2] = matrix[2][2] - mat[2][2];

#endif

        return m;
    }

    Matrix& Matrix::operator-=(const Matrix &mat) {
        *this = *this - mat;
        return *this;
    }

    Matrix Matrix::operator*(const float k) const {
        Matrix m;

#if defined(USE_AVX2)

        const __m256 first = _mm256_set_ps(matrix[2][1], matrix[2][0], matrix[1][2], matrix[1][1], matrix[1][0], matrix[0][2], matrix[0][1], matrix[0][0]);
        const __m256 second = _mm256_set1_ps(k);
        const __m256 sum = _mm256_mul_ps(first, second);

        _mm256_store_ps(&m[0][0], sum);
        m[2][2] = matrix[2][2] * k;

#elif defined(USE_SSE2)

        const __m128 first = _mm_set_ps(matrix[1][0], matrix[0][2], matrix[0][1], matrix[0][0]);
        const __m128 second = _mm_set_ps(matrix[2][1], matrix[2][0], matrix[1][2], matrix[1][1]);
        const __m128 third = _mm_set1_ps(k);

        const __m128 sum1 = _mm_mul_ps(first, third);
        const __m128 sum2 = _mm_mul_ps(second, third);

        _mm_store_ps(&m[0][0], sum1);
        _mm_store_ps(&m[1][1], sum2);
        m[2][2] = matrix[2][2] * k;

#else

        m[0][0] = matrix[0][0] * k;
        m[0][1] = matrix[0][1] * k;
        m[0][2] = matrix[0][2] * k;
        m[1][0] = matrix[1][0] * k;
        m[1][1] = matrix[1][1] * k;
        m[1][2] = matrix[1][2] * k;
        m[2][0] = matrix[2][0] * k;
        m[2][1] = matrix[2][1] * k;
        m[2][2] = matrix[2][2] * k;

#endif

        return m;
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
        Matrix m;

#if defined(USE_AVX2)

        const __m256 row0_0 = _mm256_set_ps(0.f, matrix[0][2], matrix[0][1], matrix[0][0], 0.f, matrix[0][2], matrix[0][1], matrix[0][0]);
        const __m256 row1_1 = _mm256_set_ps(0.f, matrix[1][2], matrix[1][1], matrix[1][0], 0.f, matrix[1][2], matrix[1][1], matrix[1][0]);
        const __m256 row2_2 = _mm256_set_ps(0.f, matrix[2][2], matrix[2][1], matrix[2][0], 0.f, matrix[2][2], matrix[2][1], matrix[2][0]);
        const __m256 row0_1 = _mm256_set_ps(0.f, matrix[1][2], matrix[1][1], matrix[1][0], 0.f, matrix[0][2], matrix[0][1], matrix[0][0]);
        const __m256 col0_1 = _mm256_set_ps(0.f, mat[2][1], mat[1][1], mat[0][1], 0.f, mat[2][0], mat[1][0], mat[0][0]);
        const __m256 col2_2 = _mm256_set_ps(0.f, mat[2][2], mat[1][2], mat[0][2], 0.f, mat[2][2], mat[1][2], mat[0][2]);

        __m256 row0col0xrow0col1 = _mm256_mul_ps(row0_0, col0_1);
        __m256 row1col0xrow1col1 = _mm256_mul_ps(row1_1, col0_1);
        __m256 row2col0xrow2col1 = _mm256_mul_ps(row2_2, col0_1);
        __m256 row0col2xrow1col2 = _mm256_mul_ps(row0_1, col2_2);
        __m256 row2col2xrow2col2 = _mm256_mul_ps(row2_2, col2_2);

        row0col0xrow0col1 = _mm256_hadd_ps(_mm256_hadd_ps(row0col0xrow0col1, row0col0xrow0col1), row0col0xrow0col1);
        row1col0xrow1col1 = _mm256_hadd_ps(_mm256_hadd_ps(row1col0xrow1col1, row1col0xrow1col1), row1col0xrow1col1);
        row2col0xrow2col1 = _mm256_hadd_ps(_mm256_hadd_ps(row2col0xrow2col1, row2col0xrow2col1), row2col0xrow2col1);
        row0col2xrow1col2 = _mm256_hadd_ps(_mm256_hadd_ps(row0col2xrow1col2, row0col2xrow1col2), row0col2xrow1col2);
        row2col2xrow2col2 = _mm256_hadd_ps(_mm256_hadd_ps(row2col2xrow2col2, row2col2xrow2col2), row2col2xrow2col2);

        m[0][0] = row0col0xrow0col1[0];
        m[0][1] = row0col0xrow0col1[4];
        m[0][2] = row0col2xrow1col2[0];
        m[1][0] = row1col0xrow1col1[0];
        m[1][1] = row1col0xrow1col1[4];
        m[1][2] = row0col2xrow1col2[4];
        m[2][0] = row2col0xrow2col1[0];
        m[2][1] = row2col0xrow2col1[4];
        m[2][2] = row2col2xrow2col2[0];

#elif defined(USE_SSE2)

        const __m128 row0 = _mm_set_ps(0.f, matrix[0][2], matrix[0][1], matrix[0][0]);
        const __m128 row1 = _mm_set_ps(0.f, matrix[1][2], matrix[1][1], matrix[1][0]);
        const __m128 row2 = _mm_set_ps(0.f, matrix[2][2], matrix[2][1], matrix[2][0]);
        const __m128 col0 = _mm_set_ps(0.f, mat[2][0], mat[1][0], mat[0][0]);
        const __m128 col1 = _mm_set_ps(0.f, mat[2][1], mat[1][1], mat[0][1]);
        const __m128 col2 = _mm_set_ps(0.f, mat[2][2], mat[1][2], mat[0][2]);

        const __m128 m00 = _mm_mul_ps(row0, col0);
        const __m128 m01 = _mm_mul_ps(row0, col1);
        const __m128 m02 = _mm_mul_ps(row0, col2);
        const __m128 m10 = _mm_mul_ps(row1, col0);
        const __m128 m11 = _mm_mul_ps(row1, col1);
        const __m128 m12 = _mm_mul_ps(row1, col2);
        const __m128 m20 = _mm_mul_ps(row2, col0);
        const __m128 m21 = _mm_mul_ps(row2, col1);
        const __m128 m22 = _mm_mul_ps(row2, col2);

        m[0][0] = m00[0] + m00[1] + m00[2];
        m[0][1] = m01[0] + m01[1] + m01[2];
        m[0][2] = m02[0] + m02[1] + m02[2];
        m[1][0] = m10[0] + m10[1] + m10[2];
        m[1][1] = m11[0] + m11[1] + m11[2];
        m[1][2] = m12[0] + m12[1] + m12[2];
        m[2][0] = m20[0] + m20[1] + m20[2];
        m[2][1] = m21[0] + m21[1] + m21[2];
        m[2][2] = m22[0] + m22[1] + m22[2];

#else

        for (uint32_t i = 0; i < 3; i++) {
            for (uint32_t j = 0; j < 3; j++) {
                for (uint32_t k = 0; k < 3; k++) {
                    m[i][j] += matrix[i][k] * mat[k][j];
                }
            }
        }

#endif
        return m;
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
