#include <cstdint>

namespace EngineM::kernels::scalar {
    void matrix_add(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]) {
        out[0][0] = a[0][0] + b[0][0];
        out[0][1] = a[0][1] + b[0][1];
        out[0][2] = a[0][2] + b[0][2];
        out[1][0] = a[1][0] + b[1][0];
        out[1][1] = a[1][1] + b[1][1];
        out[1][2] = a[1][2] + b[1][2];
        out[2][0] = a[2][0] + b[2][0];
        out[2][1] = a[2][1] + b[2][1];
        out[2][2] = a[2][2] + b[2][2];
    }

    void matrix_sub(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]) {
        out[0][0] = a[0][0] - b[0][0];
        out[0][1] = a[0][1] - b[0][1];
        out[0][2] = a[0][2] - b[0][2];
        out[1][0] = a[1][0] - b[1][0];
        out[1][1] = a[1][1] - b[1][1];
        out[1][2] = a[1][2] - b[1][2];
        out[2][0] = a[2][0] - b[2][0];
        out[2][1] = a[2][1] - b[2][1];
        out[2][2] = a[2][2] - b[2][2];
    }

    void matrix_mul_by_k(const float (&a)[3][3], float k, float (&out)[3][3]) {
        out[0][0] = a[0][0] * k;
        out[0][1] = a[0][1] * k;
        out[0][2] = a[0][2] * k;
        out[1][0] = a[1][0] * k;
        out[1][1] = a[1][1] * k;
        out[1][2] = a[1][2] * k;
        out[2][0] = a[2][0] * k;
        out[2][1] = a[2][1] * k;
        out[2][2] = a[2][2] * k;
    }

    void matrix_mul(const float (&a)[3][3], const float (&b)[3][3], float (&out)[3][3]) {
        for (uint32_t i = 0; i < 3; i++) {
            for (uint32_t j = 0; j < 3; j++) {
                out[i][j] = 0.0f;
                for (uint32_t k = 0; k < 3; k++) {
                    out[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }
}