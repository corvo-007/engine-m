#include <immintrin.h>

namespace EngineM::kernels::avx {
    void matrix_add(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]) {
        const __m256 first = _mm256_set_ps(a[2][1], a[2][0], a[1][2], a[1][1], a[1][0], a[0][2], a[0][1], a[0][0]);
        const __m256 second = _mm256_set_ps(b[2][1], b[2][0], b[1][2], b[1][1], b[1][0], b[0][2], b[0][1], b[0][0]);
        const __m256 result = _mm256_add_ps(first, second);

        _mm256_store_ps(&out[0][0], result);
        out[2][2] = a[2][2] + b[2][2];
    }

    void matrix_sub(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]) {
        const __m256 first = _mm256_set_ps(a[2][1], a[2][0], a[1][2], a[1][1], a[1][0], a[0][2], a[0][1], a[0][0]);
        const __m256 second = _mm256_set_ps(b[2][1], b[2][0], b[1][2], b[1][1], b[1][0], b[0][2], b[0][1], b[0][0]);
        const __m256 result = _mm256_sub_ps(first, second);

        _mm256_store_ps(&out[0][0], result);
        out[2][2] = a[2][2] - b[2][2];
    }

    void matrix_mul_by_k(const float (&a)[3][3], float k, float (&out)[3][3]) {
        const __m256 first = _mm256_set_ps(a[2][1], a[2][0], a[1][2], a[1][1], a[1][0], a[0][2], a[0][1], a[0][0]);
        const __m256 second = _mm256_set1_ps(k);
        const __m256 result = _mm256_mul_ps(first, second);

        _mm256_store_ps(&out[0][0], result);
        out[2][2] = a[2][2] * k;
    }

    void matrix_mul(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]) {
        const __m256 row0_0 = _mm256_set_ps(0.f, a[0][2], a[0][1], a[0][0], 0.f, a[0][2], a[0][1], a[0][0]);
        const __m256 row1_1 = _mm256_set_ps(0.f, a[1][2], a[1][1], a[1][0], 0.f, a[1][2], a[1][1], a[1][0]);
        const __m256 row2_2 = _mm256_set_ps(0.f, a[2][2], a[2][1], a[2][0], 0.f, a[2][2], a[2][1], a[2][0]);
        const __m256 row0_1 = _mm256_set_ps(0.f, a[1][2], a[1][1], a[1][0], 0.f, a[0][2], a[0][1], a[0][0]);
        const __m256 col0_1 = _mm256_set_ps(0.f, b[2][1], b[1][1], b[0][1], 0.f, b[2][0], b[1][0], b[0][0]);
        const __m256 col2_2 = _mm256_set_ps(0.f, b[2][2], b[1][2], b[0][2], 0.f, b[2][2], b[1][2], b[0][2]);

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

        alignas(32) float arr1[8];
        alignas(32) float arr2[8];
        alignas(32) float arr3[8];
        alignas(32) float arr4[8];
        alignas(32) float arr5[8];

        _mm256_store_ps(arr1, row0col0xrow0col1);
        _mm256_store_ps(arr2, row0col2xrow1col2);
        _mm256_store_ps(arr3, row1col0xrow1col1);
        _mm256_store_ps(arr4, row2col0xrow2col1);
        _mm256_store_ps(arr5, row2col2xrow2col2);


        out[0][0] = arr1[0];
        out[0][1] = arr1[4];
        out[0][2] = arr2[0];
        out[1][0] = arr3[0];
        out[1][1] = arr3[4];
        out[1][2] = arr2[4];
        out[2][0] = arr4[0];
        out[2][1] = arr4[4];
        out[2][2] = arr5[0];
    }
}