#include <cmath>
#include <gtest/gtest.h>

#include "quaternion/quaternion.h"

TEST(QuaternionTest, DefaultConstruct) {
    const MathEngine::Quaternion q;

    EXPECT_FLOAT_EQ(q.a, 0);
    EXPECT_FLOAT_EQ(q.v.x, 0);
    EXPECT_FLOAT_EQ(q.v.y, 0);
    EXPECT_FLOAT_EQ(q.v.z, 0);
}

TEST(QuaternionTest, ParamConstruct) {
    const MathEngine::Quaternion q(1, MathEngine::Vector3d(2, 3, 4));

    EXPECT_FLOAT_EQ(q.a, 1);
    EXPECT_FLOAT_EQ(q.v.x, 2);
    EXPECT_FLOAT_EQ(q.v.y, 3);
    EXPECT_FLOAT_EQ(q.v.z, 4);
}

TEST(QuaternionTest, CopyConstruct) {
    const MathEngine::Quaternion q1(1, MathEngine::Vector3d(2, 3, 4));
    const MathEngine::Quaternion q2(q1);

    EXPECT_FLOAT_EQ(q1.a, q2.a);
    EXPECT_FLOAT_EQ(q1.v.x, q2.v.x);
    EXPECT_FLOAT_EQ(q1.v.y, q2.v.y);
    EXPECT_FLOAT_EQ(q1.v.z, q2.v.z);
}

TEST(QuaternionTest, AssignmentOp) {
    MathEngine::Quaternion q1;
    const MathEngine::Quaternion q2(1, MathEngine::Vector3d(2, 3, 4));

    EXPECT_FLOAT_EQ(q1.a, 0);
    EXPECT_FLOAT_EQ(q1.v.x, 0);
    EXPECT_FLOAT_EQ(q1.v.y, 0);
    EXPECT_FLOAT_EQ(q1.v.z, 0);

    q1 = q2;

    EXPECT_FLOAT_EQ(q1.a, 1);
    EXPECT_FLOAT_EQ(q1.v.x, 2);
    EXPECT_FLOAT_EQ(q1.v.y, 3);
    EXPECT_FLOAT_EQ(q1.v.z, 4);
}

TEST(QuaternionTest, Add) {
    const MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q2(15.3, MathEngine::Vector3d(2.0, 3.2, 4.0));
    const MathEngine::Quaternion q3 = q1 + q2;

    EXPECT_FLOAT_EQ(q3.a, q1.a + q2.a);
    EXPECT_FLOAT_EQ(q3.v.x, q1.v.x + q2.v.x);
    EXPECT_FLOAT_EQ(q3.v.y, q1.v.y + q2.v.y);
    EXPECT_FLOAT_EQ(q3.v.z, q1.v.z + q2.v.z);
}

TEST(QuaternionTest, AddEqual) {
    MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q2(15.3, MathEngine::Vector3d(2.0, 3.2, 4.0));
    const MathEngine::Quaternion q3 = q1;

    q1 += q2;

    EXPECT_FLOAT_EQ(q1.a, q3.a + q2.a);
    EXPECT_FLOAT_EQ(q1.v.x, q3.v.x + q2.v.x);
    EXPECT_FLOAT_EQ(q1.v.y, q3.v.y + q2.v.y);
    EXPECT_FLOAT_EQ(q1.v.z, q3.v.z + q2.v.z);
}

TEST(QuaternionTest, Sub) {
    const MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q2(15.3, MathEngine::Vector3d(2.0, 3.2, 4.0));
    const MathEngine::Quaternion q3 = q1 - q2;

    EXPECT_FLOAT_EQ(q3.a, q1.a - q2.a);
    EXPECT_FLOAT_EQ(q3.v.x, q1.v.x - q2.v.x);
    EXPECT_FLOAT_EQ(q3.v.y, q1.v.y - q2.v.y);
    EXPECT_FLOAT_EQ(q3.v.z, q1.v.z - q2.v.z);
}

TEST(QuaternionTest, SubEqual) {
    MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q2(15.3, MathEngine::Vector3d(2.0, 3.2, 4.0));
    const MathEngine::Quaternion q3 = q1;

    q1 -= q2;

    EXPECT_FLOAT_EQ(q1.a, q3.a - q2.a);
    EXPECT_FLOAT_EQ(q1.v.x, q3.v.x - q2.v.x);
    EXPECT_FLOAT_EQ(q1.v.y, q3.v.y - q2.v.y);
    EXPECT_FLOAT_EQ(q1.v.z, q3.v.z - q2.v.z);
}

TEST(QuaternionTest, QuaternionMul) {
    const MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q2(15.3, MathEngine::Vector3d(2.0, 3.2, 4.0));

    const MathEngine::Quaternion result = q1 * q2;

    EXPECT_FLOAT_EQ(result.a, q1.a * q2.a - q1.v * q2.v);
    EXPECT_FLOAT_EQ(result.v.x, (q1.v * q2.a + q2.v * q1.a + (q1.v ^ q2.v)).x);
    EXPECT_FLOAT_EQ(result.v.y, (q1.v * q2.a + q2.v * q1.a + (q1.v ^ q2.v)).y);
    EXPECT_FLOAT_EQ(result.v.z, (q1.v * q2.a + q2.v * q1.a + (q1.v ^ q2.v)).z);
}

TEST(QuaternionTest, QuaternionMulEqual) {
    MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q2(15.3, MathEngine::Vector3d(2.0, 3.2, 4.0));
    const MathEngine::Quaternion q3 = q1;

    q1 *= q2;

    EXPECT_FLOAT_EQ(q1.a, q3.a * q2.a - q3.v * q2.v);
    EXPECT_FLOAT_EQ(q1.v.x, (q3.v * q2.a + q2.v * q3.a + (q3.v ^ q2.v)).x);
    EXPECT_FLOAT_EQ(q1.v.y, (q3.v * q2.a + q2.v * q3.a + (q3.v ^ q2.v)).y);
    EXPECT_FLOAT_EQ(q1.v.z, (q3.v * q2.a + q2.v * q3.a + (q3.v ^ q2.v)).z);
}

TEST(QuaternionTest, ScalarMul) {
    const MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    constexpr float k = 3.2;

    const MathEngine::Quaternion result = q1 * k;

    EXPECT_FLOAT_EQ(result.a, q1.a * k);
    EXPECT_FLOAT_EQ(result.v.x, q1.v.x * k);
    EXPECT_FLOAT_EQ(result.v.y, q1.v.y * k);
    EXPECT_FLOAT_EQ(result.v.z, q1.v.z * k);
}

TEST(QuaternionTest, ScalarMulEqual) {
    MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q2 = q1;
    constexpr float k = 3.2;

    q1 *= k;

    EXPECT_FLOAT_EQ(q1.a, q2.a * k);
    EXPECT_FLOAT_EQ(q1.v.x, q2.v.x * k);
    EXPECT_FLOAT_EQ(q1.v.y, q2.v.y * k);
    EXPECT_FLOAT_EQ(q1.v.z, q2.v.z * k);
}

TEST(QuaternionTest, ScalarDiv) {
    const MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    constexpr float k = 3.2;

    const MathEngine::Quaternion result = q1 / k;

    EXPECT_FLOAT_EQ(result.a, q1.a / k);
    EXPECT_FLOAT_EQ(result.v.x, q1.v.x / k);
    EXPECT_FLOAT_EQ(result.v.y, q1.v.y / k);
    EXPECT_FLOAT_EQ(result.v.z, q1.v.z / k);
}

TEST(QuaternionTest, ScalarDivEqual) {
    MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q2 = q1;
    constexpr float k = 3.2;

    q1 /= k;

    EXPECT_FLOAT_EQ(q1.a, q2.a / k);
    EXPECT_FLOAT_EQ(q1.v.x, q2.v.x / k);
    EXPECT_FLOAT_EQ(q1.v.y, q2.v.y / k);
    EXPECT_FLOAT_EQ(q1.v.z, q2.v.z / k);
}

TEST(QuaternionTest, Equal) {
    const MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q2(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q3(2.4, MathEngine::Vector3d(1.2, 3.6, 2.4));

    EXPECT_TRUE(q1 == q2);
    EXPECT_FALSE(q1 == q3);
}

TEST(QuaternionTest, NotEqual) {
    const MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q2(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q3(2.4, MathEngine::Vector3d(1.2, 3.6, 2.4));

    EXPECT_FALSE(q1 != q2);
    EXPECT_TRUE(q1 != q3);
}

TEST(QuaternionTest, Norm) {
    const MathEngine::Quaternion q(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const float result = q.norm();

    EXPECT_FLOAT_EQ(result, std::sqrt(q.a * q.a + q.v.x * q.v.x + q.v.y * q.v.y + q.v.z * q.v.z));
}

TEST(QuaternionTest, Normalise) {
    MathEngine::Quaternion q1(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion q2 = q1;

    q1.normalise();

    EXPECT_FLOAT_EQ(q1.a, q2.a / q2.norm());
    EXPECT_FLOAT_EQ(q1.v.x, q2.v.x / q2.norm());
    EXPECT_FLOAT_EQ(q1.v.y, q2.v.y / q2.norm());
    EXPECT_FLOAT_EQ(q1.v.z, q2.v.z / q2.norm());
    EXPECT_FLOAT_EQ(q1.norm(), 1);
}

TEST(QuaternionTest, Conjugate) {
    const MathEngine::Quaternion q(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion result = q.conjugate();

    EXPECT_FLOAT_EQ(result.a, q.a);
    EXPECT_FLOAT_EQ(result.v.x, -q.v.x);
    EXPECT_FLOAT_EQ(result.v.y, -q.v.y);
    EXPECT_FLOAT_EQ(result.v.z, -q.v.z);
}

TEST(QuaternionTest, Inverse) {
    const MathEngine::Quaternion q(4.2, MathEngine::Vector3d(2.1, 6.3, 4.2));
    const MathEngine::Quaternion result = q.inverse();

    float n = q.norm();
    n *= n;

    EXPECT_FLOAT_EQ(result.a, q.a / n);
    EXPECT_FLOAT_EQ(result.v.x, -q.v.x / n);
    EXPECT_FLOAT_EQ(result.v.y, -q.v.y / n);
    EXPECT_FLOAT_EQ(result.v.z, -q.v.z / n);
}
