#include <cmath>
#include <gtest/gtest.h>

#include "vector/vector2d.h"
#include "constants.h"

TEST(Vector2dTest, DefaultConstruct) {
    const MathEngine::Vector2d v;

    EXPECT_FLOAT_EQ(v.x, 0);
    EXPECT_FLOAT_EQ(v.y, 0);
}

TEST(Vector2dTest, ParamConstruct) {
    const MathEngine::Vector2d v(1.3, 6.7);

    EXPECT_FLOAT_EQ(v.x, 1.3);
    EXPECT_FLOAT_EQ(v.y, 6.7);
}

TEST(Vector2dTest, CopyConstruct) {
    const MathEngine::Vector2d v1(1.3, 6.7);
    const MathEngine::Vector2d v2 = v1;

    EXPECT_FLOAT_EQ(v1.x, v2.x);
    EXPECT_FLOAT_EQ(v1.y, v2.y);
}

TEST(Vector2dTest, AssignmentOp) {
    const MathEngine::Vector2d v1(1.3, 6.7);
    MathEngine::Vector2d v2(3, 2);

    EXPECT_FLOAT_EQ(v2.x, 3);
    EXPECT_FLOAT_EQ(v2.y, 2);

    v2 = v1;

    EXPECT_FLOAT_EQ(v1.x, v2.x);
    EXPECT_FLOAT_EQ(v1.y, v2.y);
}

TEST(Vector2dTest, Add) {
    const MathEngine::Vector2d v1(1.5, 2.5);
    const MathEngine::Vector2d v2(8.2, 5.2);

    const MathEngine::Vector2d result = v1 + v2;

    EXPECT_FLOAT_EQ(result.x, 9.7);
    EXPECT_FLOAT_EQ(result.y, 7.7);
}

TEST(Vector2dTest, AddEqual) {
    MathEngine::Vector2d v1(1.5, 2.5);
    const MathEngine::Vector2d v2(8.2, 5.2);

    EXPECT_FLOAT_EQ(v1.x, 1.5);
    EXPECT_FLOAT_EQ(v1.y, 2.5);

    v1 += v2;

    EXPECT_FLOAT_EQ(v1.x, 9.7);
    EXPECT_FLOAT_EQ(v1.y, 7.7);
}

TEST(Vector2dTest, Sub) {
    const MathEngine::Vector2d v1(1.5, 2.5);
    const MathEngine::Vector2d v2(8.2, 5.2);

    const MathEngine::Vector2d result = v1 - v2;

    EXPECT_FLOAT_EQ(result.x, -6.7);
    EXPECT_FLOAT_EQ(result.y, -2.7);
}

TEST(Vector2dTest, SubEqual) {
    MathEngine::Vector2d v1(1.5, 2.5);
    const MathEngine::Vector2d v2(8.2, 5.2);

    EXPECT_FLOAT_EQ(v1.x, 1.5);
    EXPECT_FLOAT_EQ(v1.y, 2.5);

    v1 -= v2;

    EXPECT_FLOAT_EQ(v1.x, -6.7);
    EXPECT_FLOAT_EQ(v1.y, -2.7);
}

TEST(Vector2dTest, ScalarMul) {
    const MathEngine::Vector2d v1(1.5, 2.5);
    constexpr float k = 2.5;
    const MathEngine::Vector2d result = v1 * k;

    EXPECT_FLOAT_EQ(result.x, 1.5 * k);
    EXPECT_FLOAT_EQ(result.y, 2.5 * k);
}

TEST(Vector2dTest, ScalarMulEqual) {
    MathEngine::Vector2d v1(1.5, 2.5);
    constexpr float k = 2.5;

    EXPECT_FLOAT_EQ(v1.x, 1.5);
    EXPECT_FLOAT_EQ(v1.y, 2.5);

    v1 *= k;

    EXPECT_FLOAT_EQ(v1.x, 1.5 * k);
    EXPECT_FLOAT_EQ(v1.y, 2.5 * k);
}

TEST(Vector2dTest, ScalarDiv) {
    const MathEngine::Vector2d v1(5.2, 2.9);
    constexpr float k = 2.9;

    const MathEngine::Vector2d result = v1 / k;

    EXPECT_FLOAT_EQ(result.x, 5.2 / k);
    EXPECT_FLOAT_EQ(result.y, 2.9 / k);
}

TEST(Vector2dTest, ScalarDivEqual) {
    MathEngine::Vector2d v1(5.2, 2.9);
    constexpr float k = 2.9;

    EXPECT_FLOAT_EQ(v1.x, 5.2);
    EXPECT_FLOAT_EQ(v1.y, 2.9);

    v1 /= k;

    EXPECT_FLOAT_EQ(v1.x, 5.2 / k);
    EXPECT_FLOAT_EQ(v1.y, 1);
}

TEST(Vector2dTest, Negate) {
    const MathEngine::Vector2d v(5.56, -9.2);
    const MathEngine::Vector2d result = -v;

    EXPECT_FLOAT_EQ(result.x, -5.56);
    EXPECT_FLOAT_EQ(result.y, 9.2);
}

TEST(Vector2dTest, DotProduct) {
    const MathEngine::Vector2d v1(5, 5);
    const MathEngine::Vector2d v2(3, 4);

    const float result = v1.dot(v2);

    EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y);
}

TEST(Vector2dTest, DotProductOperator) {
    const MathEngine::Vector2d v1(5, 5);
    const MathEngine::Vector2d v2(3, 4);

    const float result = v1 * v2;

    EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y);
}

TEST(Vector2dTest, CrossProduct) {
    const MathEngine::Vector2d v1(5, 5);
    const MathEngine::Vector2d v2(3, 4);

    const MathEngine::Vector3d result = v1.cross(v2);

    EXPECT_FLOAT_EQ(result.x, 0);
    EXPECT_FLOAT_EQ(result.y, 0);
    EXPECT_FLOAT_EQ(result.z, v1.x * v2.y - v2.x * v1.y);
}

TEST(Vector2dTest, CrossProductOperator) {
    const MathEngine::Vector2d v1(5, 5);
    const MathEngine::Vector2d v2(3, 4);

    const MathEngine::Vector3d result = v1 ^ v2;

    EXPECT_FLOAT_EQ(result.x, 0);
    EXPECT_FLOAT_EQ(result.y, 0);
    EXPECT_FLOAT_EQ(result.z, v1.x * v2.y - v2.x * v1.y);
}

TEST(Vector2dTest, Equal) {
    const MathEngine::Vector2d v1(5, 5);
    const MathEngine::Vector2d v2(3, 4);
    const MathEngine::Vector2d v3(3, 4);

    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v2 == v3);
}

TEST(Vector2dTest, NotEqual) {
    const MathEngine::Vector2d v1(5, 5);
    const MathEngine::Vector2d v2(3, 4);
    const MathEngine::Vector2d v3(3, 4);

    EXPECT_TRUE(v1 != v2);
    EXPECT_FALSE(v2 != v3);
}

TEST(Vector2dTest, Magnitude) {
    const MathEngine::Vector2d v(5.3, 2.9);

    EXPECT_FLOAT_EQ(v.magnitude(), std::sqrt(v.x * v.x + v.y * v.y));
}

TEST(Vector2dTest, Normalise) {
    MathEngine::Vector2d v1(5.3, 2.9);
    const MathEngine::Vector2d v2 = v1;

    v1.normalise();
    EXPECT_FLOAT_EQ(v1.x, v2.x / v2.magnitude());
    EXPECT_FLOAT_EQ(v1.y, v2.y / v2.magnitude());
    EXPECT_FLOAT_EQ(v1.magnitude(), 1);

}

TEST(Vector2dTest, Rotate) {
    const MathEngine::Vector2d v1(1, 0);
    MathEngine::Vector2d v2 = v1.rotate(90);

    EXPECT_NEAR(v2.x, 0, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 1, MathEngine::epsilon);

    v2 = v1.rotate(180);

    EXPECT_NEAR(v2.x, -1, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 0, MathEngine::epsilon);
}

TEST(Vector2dTest, RotateRad) {
    const MathEngine::Vector2d v1(1, 0);
    MathEngine::Vector2d v2 = v1.rotateRad(MathEngine::PI / 2);

    EXPECT_NEAR(v2.x, 0, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 1, MathEngine::epsilon);

    v2 = v1.rotateRad(MathEngine::PI);

    EXPECT_NEAR(v2.x, -1, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 0, MathEngine::epsilon);
}
