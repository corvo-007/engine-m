#pragma once

namespace EngineM::kernels {
    namespace avx512 {
        void matrix_add(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        void matrix_sub(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        void matrix_mul_by_k(const float (&a)[3][3], float k, float (&out)[3][3]);
        void matrix_mul(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
    }

    namespace avx2 {
        void matrix_add(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        void matrix_sub(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        void matrix_mul_by_k(const float (&a)[3][3], float k, float (&out)[3][3]);
        void matrix_mul(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
    }

    namespace avx {
        void matrix_add(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        void matrix_sub(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        void matrix_mul_by_k(const float (&a)[3][3], float k, float (&out)[3][3]);
        void matrix_mul(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
    }

    namespace sse {
        void matrix_add(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        void matrix_sub(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        void matrix_mul_by_k(const float (&a)[3][3], float k, float (&out)[3][3]);
        void matrix_mul(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
    }

    namespace scalar {
        void matrix_add(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        void matrix_sub(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
        void matrix_mul_by_k(const float (&a)[3][3], float k, float (&out)[3][3]);
        void matrix_mul(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]);
    }
}