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

        float arr1[4], arr2[4], arr3[4], arr4[4], arr5[4], arr6[4], arr7[4], arr8[4], arr9[4];

        _mm_store_ps(arr1, m00);
        _mm_store_ps(arr2, m01);
        _mm_store_ps(arr3, m02);
        _mm_store_ps(arr4, m10);
        _mm_store_ps(arr5, m11);
        _mm_store_ps(arr6, m12);
        _mm_store_ps(arr7, m20);
        _mm_store_ps(arr8, m21);
        _mm_store_ps(arr9, m22);

        out[0][0] = arr1[0] + arr1[1] + arr1[2];
        out[0][1] = arr2[0] + arr2[1] + arr2[2];
        out[0][2] = arr3[0] + arr3[1] + arr3[2];
        out[1][0] = arr4[0] + arr4[1] + arr4[2];
        out[1][1] = arr5[0] + arr5[1] + arr5[2];
        out[1][2] = arr6[0] + arr6[1] + arr6[2];
        out[2][0] = arr7[0] + arr7[1] + arr7[2];
        out[2][1] = arr8[0] + arr8[1] + arr8[2];
        out[2][2] = arr9[0] + arr9[1] + arr9[2];
    }
}