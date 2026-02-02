#include <immintrin.h>

namespace EngineM::kernels::sse {
    void matrix_add(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]) {
        const __m128 first = _mm_set_ps(a[1][0], a[0][2], a[0][1], a[0][0]);
        const __m128 second = _mm_set_ps(a[2][1], a[2][0], a[1][2], a[1][1]);
        const __m128 third = _mm_set_ps(b[1][0], b[0][2], b[0][1], b[0][0]);
        const __m128 fourth = _mm_set_ps(b[2][1], b[2][0], b[1][2], b[1][1]);

        const __m128 output1 = _mm_add_ps(first, third);
        const __m128 output2 = _mm_add_ps(second, fourth);

        _mm_store_ps(&out[0][0], output1);
        _mm_store_ps(&out[1][1], output2);
        out[2][2] = a[2][2] + b[2][2];
    }

    void matrix_sub(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]) {
        const __m128 first = _mm_set_ps(a[1][0], a[0][2], a[0][1], a[0][0]);
        const __m128 second = _mm_set_ps(a[2][1], a[2][0], a[1][2], a[1][1]);
        const __m128 third = _mm_set_ps(b[1][0], b[0][2], b[0][1], b[0][0]);
        const __m128 fourth = _mm_set_ps(b[2][1], b[2][0], b[1][2], b[1][1]);

        const __m128 output1 = _mm_sub_ps(first, third);
        const __m128 output2 = _mm_sub_ps(second, fourth);

        _mm_store_ps(&out[0][0], output1);
        _mm_store_ps(&out[1][1], output2);
        out[2][2] = a[2][2] - b[2][2];
    }

    void matrix_mul_by_k(const float (&a)[3][3], float k, float (&out)[3][3]) {
        const __m128 first = _mm_set_ps(a[1][0], a[0][2], a[0][1], a[0][0]);
        const __m128 second = _mm_set_ps(a[2][1], a[2][0], a[1][2], a[1][1]);
        const __m128 third = _mm_set1_ps(k);

        const __m128 output1 = _mm_mul_ps(first, third);
        const __m128 output2 = _mm_mul_ps(second, third);

        _mm_store_ps(&out[0][0], output1);
        _mm_store_ps(&out[1][1], output2);
        out[2][2] = a[2][2] * k;
    }

    void matrix_mul(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]) {
        const __m128 row0 = _mm_set_ps(0.f, a[0][2], a[0][1], a[0][0]);
        const __m128 row1 = _mm_set_ps(0.f, a[1][2], a[1][1], a[1][0]);
        const __m128 row2 = _mm_set_ps(0.f, a[2][2], a[2][1], a[2][0]);
        const __m128 col0 = _mm_set_ps(0.f, b[2][0], b[1][0], b[0][0]);
        const __m128 col1 = _mm_set_ps(0.f, b[2][1], b[1][1], b[0][1]);
        const __m128 col2 = _mm_set_ps(0.f, b[2][2], b[1][2], b[0][2]);

        const __m128 m00 = _mm_mul_ps(row0, col0);
        const __m128 m01 = _mm_mul_ps(row0, col1);
        const __m128 m02 = _mm_mul_ps(row0, col2);
        const __m128 m10 = _mm_mul_ps(row1, col0);
        const __m128 m11 = _mm_mul_ps(row1, col1);
        const __m128 m12 = _mm_mul_ps(row1, col2);
        const __m128 m20 = _mm_mul_ps(row2, col0);
        const __m128 m21 = _mm_mul_ps(row2, col1);
        const __m128 m22 = _mm_mul_ps(row2, col2);

        out[0][0] = m00[0] + m00[1] + m00[2];
        out[0][1] = m01[0] + m01[1] + m01[2];
        out[0][2] = m02[0] + m02[1] + m02[2];
        out[1][0] = m10[0] + m10[1] + m10[2];
        out[1][1] = m11[0] + m11[1] + m11[2];
        out[1][2] = m12[0] + m12[1] + m12[2];
        out[2][0] = m20[0] + m20[1] + m20[2];
        out[2][1] = m21[0] + m21[1] + m21[2];
        out[2][2] = m22[0] + m22[1] + m22[2];
    }
}