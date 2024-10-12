#include <gtest/gtest.h>

#include "matrix/matrix.h"

TEST(MatrixTest, DefaultConstruct) {
    const MathEngine::Matrix matrix;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(matrix[i][j], 0);
        }
    }
}

TEST(MatrixTest, ParamConstruct1) {
    MathEngine::Matrix matrix(10, 9, 8, 7, 6, 5, 4, 3, 2);

    int k = 10;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(matrix[i][j], k--);
        }
    }
}

TEST(MatrixTest, ParamConstruct2) {
    constexpr float matrix[3][3] = {{10, 9, 8}, {7, 6, 5}, {4, 3, 2}};
    MathEngine::Matrix m(matrix);

    int k = 10;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(m[i][j], k--);
        }
    }
}

TEST(MatrixTest, CopyConstruct) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);
    const MathEngine::Matrix m2(m1);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(m2[i][j], m1[i][j]);
        }
    }
}

TEST(MatrixTest, AssignmentOp) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);
    MathEngine::Matrix m2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(m2[i][j], 0);
        }
    }

    m2 = m1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(m2[i][j], m1[i][j]);
        }
    }
}

TEST(MatrixTest, Add) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);
    const MathEngine::Matrix m2(3, 4, 2, 5, 1, 9, 9, 2, 1);

    const MathEngine::Matrix result = m1 + m2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(result[i][j], m1[i][j] + m2[i][j]);
        }
    }
}

TEST(MatrixTest, AddEqual) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);
    const MathEngine::Matrix m2(3, 4, 2, 5, 1, 9, 9, 2, 1);

    MathEngine::Matrix result = m1;

    result += m2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(result[i][j], m1[i][j] + m2[i][j]);
        }
    }
}

TEST(MatrixTest, Sub) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);
    const MathEngine::Matrix m2(3, 4, 2, 5, 1, 9, 9, 2, 1);

    const MathEngine::Matrix result = m1 - m2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(result[i][j], m1[i][j] - m2[i][j]);
        }
    }
}

TEST(MatrixTest, SubEqual) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);
    const MathEngine::Matrix m2(3, 4, 2, 5, 1, 9, 9, 2, 1);

    MathEngine::Matrix result = m1;

    result -= m2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(result[i][j], m1[i][j] - m2[i][j]);
        }
    }
}

TEST(MatrixTest, ScalarMul) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);

    MathEngine::Matrix result = m1 * 3.2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(result[i][j], 3.2 * m1[i][j]);
        }
    }
}

TEST(MatrixTest, ScalarMulEqual) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);

    MathEngine::Matrix result = m1;

    result *= 3.2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(result[i][j], 3.2 * m1[i][j]);
        }
    }
}

TEST(MatrixTest, ScalarDiv) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);

    MathEngine::Matrix result = m1 / 3.2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(result[i][j], m1[i][j] / 3.2);
        }
    }
}

TEST(MatrixTest, ScalarDivEqual) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);

    MathEngine::Matrix result = m1;

    result /= 3.2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(result[i][j], m1[i][j] / 3.2);
        }
    }
}

TEST(MatrixTest, Mul) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);
    const MathEngine::Matrix m2(3, 4, 2, 5, 1, 9, 9, 2, 1);

    const MathEngine::Matrix result = m1 * m2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += m1[i][k] * m2[k][j];
            }
            EXPECT_FLOAT_EQ(result[i][j], sum);
        }
    }
}

TEST(MatrixTest, MulEqual) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);
    const MathEngine::Matrix m2(3, 4, 2, 5, 1, 9, 9, 2, 1);

    MathEngine::Matrix result = m1;

    result *= m2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += m1[i][k] * m2[k][j];
            }
            EXPECT_FLOAT_EQ(result[i][j], sum);
        }
    }
}

TEST(MatrixTest, VectorMul) {
    const MathEngine::Matrix m(3, 2, 1, 6, 5, 4, 9, 8, 7);
    const MathEngine::Vector3d v(4, 3, 2);

    const MathEngine::Vector3d result = m * v;

    EXPECT_FLOAT_EQ(result.x, m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z);
    EXPECT_FLOAT_EQ(result.y, m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z);
    EXPECT_FLOAT_EQ(result.z, m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
}

TEST(MatrixTest, Equal) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);
    const MathEngine::Matrix m2(3, 4, 2, 5, 1, 9, 9, 2, 1);
    const MathEngine::Matrix m3(3, 2, 1, 6, 5, 4, 9, 8, 7);

    EXPECT_FALSE(m1 == m2);
    EXPECT_TRUE(m1 == m3);
}

TEST(MatrixTest, NotEqual) {
    const MathEngine::Matrix m1(3, 2, 1, 6, 5, 4, 9, 8, 7);
    const MathEngine::Matrix m2(3, 4, 2, 5, 1, 9, 9, 2, 1);
    const MathEngine::Matrix m3(3, 2, 1, 6, 5, 4, 9, 8, 7);

    EXPECT_TRUE(m1 != m2);
    EXPECT_FALSE(m1 != m3);
}

TEST(MatrixTest, GetInverse) {
    const MathEngine::Matrix m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    const MathEngine::Matrix m2(3, 4, 2, 5, 1, 9, 9, 2, 1);

    MathEngine::Matrix result;
    bool hasInverse = m1.getInverse(result);

    EXPECT_FALSE(hasInverse);

    hasInverse = m2.getInverse(result);
    EXPECT_TRUE(hasInverse);

    const std::vector<float> expectedResult = {-0.06666667, 0, 0.13333333, 0.29803922, -0.05882353, -0.06666667, 0.00392157,  0.11764706, -0.06666667};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(result[i][j], expectedResult[i * 3 + j]);
        }
    }
}

TEST(MatrixTest, Inverse) {
    MathEngine::Matrix m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    MathEngine::Matrix m2(3, 4, 2, 5, 1, 9, 9, 2, 1);

    bool hasInverse = m1.inverse();
    EXPECT_FALSE(hasInverse);

    hasInverse = m2.inverse();
    EXPECT_TRUE(hasInverse);

    const std::vector<float> expectedResult = {-0.06666667, 0, 0.13333333, 0.29803922, -0.05882353, -0.06666667, 0.00392157,  0.11764706, -0.06666667};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(m2[i][j], expectedResult[i * 3 + j]);
        }
    }
}

TEST(MatrixTest, GetTranspose) {
    const MathEngine::Matrix m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    const MathEngine::Matrix result = m1.getTranspose();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(result[i][j], m1[j][i]);
        }
    }
}

TEST(MatrixTest, Transpose) {
    MathEngine::Matrix m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
    const MathEngine::Matrix m2 = m1;

    m1.transpose();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(m1[i][j], m2[j][i]);
        }
    }
}

TEST(MatrixTest, Identity) {
    MathEngine::Matrix identity = MathEngine::Matrix::identity();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_FLOAT_EQ(identity[i][j], i == j ? 1 : 0);
        }
    }
}
