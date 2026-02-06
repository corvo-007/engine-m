#include <cmath>
#include <gtest/gtest.h>

#include "engine-m/vector/vector2d.h"
#include "engine-m/constants.h"

TEST(Vector2dTest, DefaultConstruct) {
    const EngineM::vec2f v;

    EXPECT_FLOAT_EQ(v.x, 0);
    EXPECT_FLOAT_EQ(v.y, 0);
}

TEST(Vector2dTest, ParamConstruct) {
    const EngineM::vec2f v(1.3, 6.7);

    EXPECT_FLOAT_EQ(v.x, 1.3);
    EXPECT_FLOAT_EQ(v.y, 6.7);
}

TEST(Vector2dTest, CopyConstruct) {
    const EngineM::vec2f v1(1.3, 6.7);
    const EngineM::vec2f v2 = v1;

    EXPECT_FLOAT_EQ(v1.x, v2.x);
    EXPECT_FLOAT_EQ(v1.y, v2.y);
}

TEST(Vector2dTest, AssignmentOp) {
    const EngineM::vec2f v1(1.3, 6.7);
    EngineM::vec2f v2(3, 2);

    EXPECT_FLOAT_EQ(v2.x, 3);
    EXPECT_FLOAT_EQ(v2.y, 2);

    v2 = v1;

    EXPECT_FLOAT_EQ(v1.x, v2.x);
    EXPECT_FLOAT_EQ(v1.y, v2.y);
}

TEST(Vector2dTest, SquareOperator) {
    EngineM::vec2f v(1.234, 6.348);

    EXPECT_FLOAT_EQ(v[0], 1.234);
    EXPECT_FLOAT_EQ(v.x, 1.234);
    EXPECT_FLOAT_EQ(v[1], 6.348);
    EXPECT_FLOAT_EQ(v.y, 6.348);

    v[0] = 1.3;
    v[1] = 2.5;

    EXPECT_FLOAT_EQ(v[0], 1.3);
    EXPECT_FLOAT_EQ(v.x, 1.3);
    EXPECT_FLOAT_EQ(v[1], 2.5);
    EXPECT_FLOAT_EQ(v.y, 2.5);
}

TEST(Vector2dTest, ConstSquareOperator) {
    const EngineM::vec2f v(1.234, 6.348);

    EXPECT_FLOAT_EQ(v[0], 1.234);
    EXPECT_FLOAT_EQ(v.x, 1.234);
    EXPECT_FLOAT_EQ(v[1], 6.348);
    EXPECT_FLOAT_EQ(v.y, 6.348);
}

TEST(Vector2dTest, Add) {
    const EngineM::vec2f v1(1.5, 2.5);
    const EngineM::vec2f v2(8.2, 5.2);

    const EngineM::vec2f result = v1 + v2;

    EXPECT_FLOAT_EQ(result.x, 9.7);
    EXPECT_FLOAT_EQ(result.y, 7.7);
}

TEST(Vector2dTest, AddEqual) {
    EngineM::vec2f v1(1.5, 2.5);
    const EngineM::vec2f v2(8.2, 5.2);

    EXPECT_FLOAT_EQ(v1.x, 1.5);
    EXPECT_FLOAT_EQ(v1.y, 2.5);

    v1 += v2;

    EXPECT_FLOAT_EQ(v1.x, 9.7);
    EXPECT_FLOAT_EQ(v1.y, 7.7);
}

TEST(Vector2dTest, Sub) {
    const EngineM::vec2f v1(1.5, 2.5);
    const EngineM::vec2f v2(8.2, 5.2);

    const EngineM::vec2f result = v1 - v2;

    EXPECT_FLOAT_EQ(result.x, -6.7);
    EXPECT_FLOAT_EQ(result.y, -2.7);
}

TEST(Vector2dTest, SubEqual) {
    EngineM::vec2f v1(1.5, 2.5);
    const EngineM::vec2f v2(8.2, 5.2);

    EXPECT_FLOAT_EQ(v1.x, 1.5);
    EXPECT_FLOAT_EQ(v1.y, 2.5);

    v1 -= v2;

    EXPECT_FLOAT_EQ(v1.x, -6.7);
    EXPECT_FLOAT_EQ(v1.y, -2.7);
}

TEST(Vector2dTest, ScalarMul) {
    const EngineM::vec2f v1(1.5, 2.5);
    constexpr float k = 2.5;
    const EngineM::vec2f result = v1 * k;

    EXPECT_FLOAT_EQ(result.x, 1.5 * k);
    EXPECT_FLOAT_EQ(result.y, 2.5 * k);
}

TEST(Vector2dTest, ScalarMulEqual) {
    EngineM::vec2f v1(1.5, 2.5);
    constexpr float k = 2.5;

    EXPECT_FLOAT_EQ(v1.x, 1.5);
    EXPECT_FLOAT_EQ(v1.y, 2.5);

    v1 *= k;

    EXPECT_FLOAT_EQ(v1.x, 1.5 * k);
    EXPECT_FLOAT_EQ(v1.y, 2.5 * k);
}

TEST(Vector2dTest, ScalarDiv) {
    const EngineM::vec2f v1(5.2, 2.9);
    constexpr float k = 2.9;

    const EngineM::vec2f result = v1 / k;

    EXPECT_FLOAT_EQ(result.x, 5.2 / k);
    EXPECT_FLOAT_EQ(result.y, 2.9 / k);
}

TEST(Vector2dTest, ScalarDivEqual) {
    EngineM::vec2f v1(5.2, 2.9);
    constexpr float k = 2.9;

    EXPECT_FLOAT_EQ(v1.x, 5.2);
    EXPECT_FLOAT_EQ(v1.y, 2.9);

    v1 /= k;

    EXPECT_FLOAT_EQ(v1.x, 5.2 / k);
    EXPECT_FLOAT_EQ(v1.y, 1);
}

TEST(Vector2dTest, Negate) {
    const EngineM::vec2f v(5.56, -9.2);
    const EngineM::vec2f result = -v;

    EXPECT_FLOAT_EQ(result.x, -5.56);
    EXPECT_FLOAT_EQ(result.y, 9.2);
}

TEST(Vector2dTest, DotProduct) {
    const EngineM::vec2f v1(5, 5);
    const EngineM::vec2f v2(3, 4);

    const float result = v1.dot(v2);

    EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y);
}

TEST(Vector2dTest, DotProductOperator) {
    const EngineM::vec2f v1(5, 5);
    const EngineM::vec2f v2(3, 4);

    const float result = v1 * v2;

    EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y);
}

TEST(Vector2dTest, CrossProduct) {
    const EngineM::vec2f v1(5, 5);
    const EngineM::vec2f v2(3, 4);

    const float result = v1.cross(v2);

    EXPECT_FLOAT_EQ(result, v1.x * v2.y - v2.x * v1.y);
}

TEST(Vector2dTest, CrossProductOperator) {
    const EngineM::vec2f v1(5, 5);
    const EngineM::vec2f v2(3, 4);

    const float result = v1 ^ v2;

    EXPECT_FLOAT_EQ(result, v1.x * v2.y - v2.x * v1.y);
}

TEST(Vector2dTest, Equal) {
    const EngineM::vec2f v1(5, 5);
    const EngineM::vec2f v2(3, 4);
    const EngineM::vec2f v3(3, 4);

    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v2 == v3);
}

TEST(Vector2dTest, NotEqual) {
    const EngineM::vec2f v1(5, 5);
    const EngineM::vec2f v2(3, 4);
    const EngineM::vec2f v3(3, 4);

    EXPECT_TRUE(v1 != v2);
    EXPECT_FALSE(v2 != v3);
}

TEST(Vector2dTest, Magnitude) {
    const EngineM::vec2f v(5.3, 2.9);

    EXPECT_FLOAT_EQ(v.magnitude(), std::sqrt(v.x * v.x + v.y * v.y));
}

TEST(Vector2dTest, Normalise) {
    EngineM::vec2f v1(5.3, 2.9);
    const EngineM::vec2f v2 = v1;

    v1.normalise();
    EXPECT_FLOAT_EQ(v1.x, v2.x / v2.magnitude());
    EXPECT_FLOAT_EQ(v1.y, v2.y / v2.magnitude());
    EXPECT_FLOAT_EQ(v1.magnitude(), 1);

}

TEST(Vector2dTest, Rotate) {
    const EngineM::vec2f v1(1, 0);
    EngineM::vec2f v2 = v1.rotate(90);

    EXPECT_NEAR(v2.x, 0, EngineM::epsilon);
    EXPECT_NEAR(v2.y, 1, EngineM::epsilon);

    v2 = v1.rotate(180);

    EXPECT_NEAR(v2.x, -1, EngineM::epsilon);
    EXPECT_NEAR(v2.y, 0, EngineM::epsilon);
}

TEST(Vector2dTest, RotateRad) {
    const EngineM::vec2f v1(1, 0);
    EngineM::vec2f v2 = v1.rotateRad(EngineM::PI / 2);

    EXPECT_NEAR(v2.x, 0, EngineM::epsilon);
    EXPECT_NEAR(v2.y, 1, EngineM::epsilon);

    v2 = v1.rotateRad(EngineM::PI);

    EXPECT_NEAR(v2.x, -1, EngineM::epsilon);
    EXPECT_NEAR(v2.y, 0, EngineM::epsilon);
}
