#include <cmath>
#include <gtest/gtest.h>

#include "vector/vector3d.h"
#include "quaternion/quaternion.h"
#include "constants.h"

TEST(Vector3dTest, DefaultConstruct) {
    const MathEngine::Vector3d v;

    EXPECT_FLOAT_EQ(v.x, 0);
    EXPECT_FLOAT_EQ(v.y, 0);
    EXPECT_FLOAT_EQ(v.z, 0);
}

TEST(Vector3dTest, ParamConstruct) {
    const MathEngine::Vector3d v(1.3, 6.7, 2.5);

    EXPECT_FLOAT_EQ(v.x, 1.3);
    EXPECT_FLOAT_EQ(v.y, 6.7);
    EXPECT_FLOAT_EQ(v.z, 2.5);
}

TEST(Vector3dTest, CopyConstruct) {
    const MathEngine::Vector3d v1(1.3, 6.7, 2.5);
    const MathEngine::Vector3d v2 = v1;

    EXPECT_FLOAT_EQ(v1.x, v2.x);
    EXPECT_FLOAT_EQ(v1.y, v2.y);
    EXPECT_FLOAT_EQ(v1.z, v2.z);
}

TEST(Vector3dTest, AssignmentOp) {
    const MathEngine::Vector3d v1(1.3, 6.7, 2.5);
    MathEngine::Vector3d v2(3, 2, 1);

    EXPECT_FLOAT_EQ(v2.x, 3);
    EXPECT_FLOAT_EQ(v2.y, 2);
    EXPECT_FLOAT_EQ(v2.z, 1);

    v2 = v1;

    EXPECT_FLOAT_EQ(v1.x, v2.x);
    EXPECT_FLOAT_EQ(v1.y, v2.y);
    EXPECT_FLOAT_EQ(v1.z, v2.z);
}

TEST(Vector3dTest, Add) {
    const MathEngine::Vector3d v1(1.5, 2.5, 5.2);
    const MathEngine::Vector3d v2(8.2, 5.2, 2.3);

    const MathEngine::Vector3d result = v1 + v2;

    EXPECT_FLOAT_EQ(result.x, 9.7);
    EXPECT_FLOAT_EQ(result.y, 7.7);
    EXPECT_FLOAT_EQ(result.z, 7.5);
}

TEST(Vector3dTest, AddEqual) {
    MathEngine::Vector3d v1(1.5, 2.5, 5.2);
    const MathEngine::Vector3d v2(8.2, 5.2, 2.3);

    EXPECT_FLOAT_EQ(v1.x, 1.5);
    EXPECT_FLOAT_EQ(v1.y, 2.5);
    EXPECT_FLOAT_EQ(v1.z, 5.2);

    v1 += v2;

    EXPECT_FLOAT_EQ(v1.x, 9.7);
    EXPECT_FLOAT_EQ(v1.y, 7.7);
    EXPECT_FLOAT_EQ(v1.z, 7.5);
}

TEST(Vector3dTest, Sub) {
    const MathEngine::Vector3d v1(1.5, 2.5, 5.2);
    const MathEngine::Vector3d v2(8.2, 5.2, 2.3);

    const MathEngine::Vector3d result = v1 - v2;

    EXPECT_FLOAT_EQ(result.x, -6.7);
    EXPECT_FLOAT_EQ(result.y, -2.7);
    EXPECT_FLOAT_EQ(result.z, 2.9);
}

TEST(Vector3dTest, SubEqual) {
    MathEngine::Vector3d v1(1.5, 2.5, 5.2);
    const MathEngine::Vector3d v2(8.2, 5.2, 2.3);

    EXPECT_FLOAT_EQ(v1.x, 1.5);
    EXPECT_FLOAT_EQ(v1.y, 2.5);
    EXPECT_FLOAT_EQ(v1.z, 5.2);

    v1 -= v2;

    EXPECT_FLOAT_EQ(v1.x, -6.7);
    EXPECT_FLOAT_EQ(v1.y, -2.7);
    EXPECT_FLOAT_EQ(v1.z, 2.9);
}

TEST(Vector3dTest, ScalarMul) {
    const MathEngine::Vector3d v1(1.5, 2.5, 5.2);
    constexpr float k = 2.5;
    const MathEngine::Vector3d result = v1 * k;

    EXPECT_FLOAT_EQ(result.x, 1.5 * k);
    EXPECT_FLOAT_EQ(result.y, 2.5 * k);
    EXPECT_FLOAT_EQ(result.z, 5.2 * k);
}

TEST(Vector3dTest, ScalarMulEqual) {
    MathEngine::Vector3d v1(1.5, 2.5, 5.2);
    constexpr float k = 2.5;

    EXPECT_FLOAT_EQ(v1.x, 1.5);
    EXPECT_FLOAT_EQ(v1.y, 2.5);
    EXPECT_FLOAT_EQ(v1.z, 5.2);

    v1 *= k;

    EXPECT_FLOAT_EQ(v1.x, 1.5 * k);
    EXPECT_FLOAT_EQ(v1.y, 2.5 * k);
    EXPECT_FLOAT_EQ(v1.z, 5.2 * k);
}

TEST(Vector3dTest, ScalarDiv) {
    const MathEngine::Vector3d v1(5.2, 2.9, 9.2);
    constexpr float k = 2.9;

    const MathEngine::Vector3d result = v1 / k;

    EXPECT_FLOAT_EQ(result.x, 5.2 / k);
    EXPECT_FLOAT_EQ(result.y, 2.9 / k);
    EXPECT_FLOAT_EQ(result.z, 9.2 / k);
}

TEST(Vector3dTest, ScalarDivEqual) {
    MathEngine::Vector3d v1(5.2, 2.9, 9.2);
    constexpr float k = 2.9;

    EXPECT_FLOAT_EQ(v1.x, 5.2);
    EXPECT_FLOAT_EQ(v1.y, 2.9);
    EXPECT_FLOAT_EQ(v1.z, 9.2);

    v1 /= k;

    EXPECT_FLOAT_EQ(v1.x, 5.2 / k);
    EXPECT_FLOAT_EQ(v1.y, 2.9 / k);
    EXPECT_FLOAT_EQ(v1.z, 9.2 / k);
}

TEST(Vector3dTest, Negate) {
    const MathEngine::Vector3d v(5.56, -9.2, 3.2);
    const MathEngine::Vector3d result = -v;

    EXPECT_FLOAT_EQ(result.x, -5.56);
    EXPECT_FLOAT_EQ(result.y, 9.2);
    EXPECT_FLOAT_EQ(result.z, -3.2);
}

TEST(Vector3dTest, DotProduct) {
    const MathEngine::Vector3d v1(5, 5, 2);
    const MathEngine::Vector3d v2(3, 4, 6);

    const float result = v1.dot(v2);

    EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

TEST(Vector3dTest, DotProductOperator) {
    const MathEngine::Vector3d v1(5, 5, 2);
    const MathEngine::Vector3d v2(3, 4, 6);

    const float result = v1 * v2;

    EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

TEST(Vector3dTest, CrossProduct) {
    const MathEngine::Vector3d v1(5, 5, 2);
    const MathEngine::Vector3d v2(3, 4, 6);

    const MathEngine::Vector3d result = v1.cross(v2);

    EXPECT_FLOAT_EQ(result.x, v1.y * v2.z - v1.z * v2.y);
    EXPECT_FLOAT_EQ(result.y, -v1.x * v2.z + v1.z * v2.x);
    EXPECT_FLOAT_EQ(result.z, v1.x * v2.y - v2.x * v1.y);
}

TEST(Vector3dTest, CrossProductOperator) {
    const MathEngine::Vector3d v1(5, 5, 2);
    const MathEngine::Vector3d v2(3, 4, 6);

    const MathEngine::Vector3d result = v1 ^ v2;

    EXPECT_FLOAT_EQ(result.x, v1.y * v2.z - v1.z * v2.y);
    EXPECT_FLOAT_EQ(result.y, -v1.x * v2.z + v1.z * v2.x);
    EXPECT_FLOAT_EQ(result.z, v1.x * v2.y - v2.x * v1.y);
}

TEST(Vector3dTest, Equal) {
    const MathEngine::Vector3d v1(5, 5, 2);
    const MathEngine::Vector3d v2(3, 4, 6);
    const MathEngine::Vector3d v3(3, 4, 6);

    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v2 == v3);
}

TEST(Vector3dTest, NotEqual) {
    const MathEngine::Vector3d v1(5, 5, 2);
    const MathEngine::Vector3d v2(3, 4, 6);
    const MathEngine::Vector3d v3(3, 4, 6);

    EXPECT_TRUE(v1 != v2);
    EXPECT_FALSE(v2 != v3);
}

TEST(Vector3dTest, Magnitude) {
    const MathEngine::Vector3d v(5.3, 2.9, 3.2);
    EXPECT_FLOAT_EQ(v.magnitude(), std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

TEST(Vector3dTest, Normalise) {
    MathEngine::Vector3d v1(5.3, 2.9, 3.2);
    const MathEngine::Vector3d v2 = v1;

    v1.normalise();
    EXPECT_FLOAT_EQ(v1.x, v2.x / v2.magnitude());
    EXPECT_FLOAT_EQ(v1.y, v2.y / v2.magnitude());
    EXPECT_FLOAT_EQ(v1.z, v2.z / v2.magnitude());
    EXPECT_FLOAT_EQ(v1.magnitude(), 1);

}

TEST(Vector3dTest, Rotate) {
    const MathEngine::Vector3d v1(1, 0, 0);
    MathEngine::Vector3d v2 = v1.rotate(90, {0, 0, 1});

    EXPECT_NEAR(v2.x, 0, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 1, MathEngine::epsilon);
    EXPECT_NEAR(v2.z, 0, MathEngine::epsilon);

    v2 = v1.rotate(180, {0, 1, 0});

    EXPECT_NEAR(v2.x, -1, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 0, MathEngine::epsilon);
    EXPECT_NEAR(v2.z, 0, MathEngine::epsilon);

    v2 = v1.rotate(360, {0, 0, 1});

    EXPECT_NEAR(v2.x, 1, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 0, MathEngine::epsilon);
    EXPECT_NEAR(v2.z, 0, MathEngine::epsilon);
}

TEST(Vector3dTest, RotateRad) {
    const MathEngine::Vector3d v1(1, 0, 0);
    MathEngine::Vector3d v2 = v1.rotateRad(MathEngine::PI / 2, {0, 0, 1});

    EXPECT_NEAR(v2.x, 0, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 1, MathEngine::epsilon);
    EXPECT_NEAR(v2.z, 0, MathEngine::epsilon);

    v2 = v1.rotateRad(MathEngine::PI, {0, 1, 0});

    EXPECT_NEAR(v2.x, -1, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 0, MathEngine::epsilon);
    EXPECT_NEAR(v2.z, 0, MathEngine::epsilon);

    v2 = v1.rotateRad(2 * MathEngine::PI, {0, 0, 1});

    EXPECT_NEAR(v2.x, 1, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 0, MathEngine::epsilon);
    EXPECT_NEAR(v2.z, 0, MathEngine::epsilon);
}

TEST(Vector3dTest, RotateByQuaternion) {
    const MathEngine::Vector3d v1(1, 0, 0);
    MathEngine::Quaternion q(cosf(MathEngine::PI / 4), MathEngine::Vector3d{0, 0, 1} * sinf(MathEngine::PI / 4));

    MathEngine::Vector3d v2 = v1.rotate(q);

    EXPECT_NEAR(v2.x, 0, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 1, MathEngine::epsilon);
    EXPECT_NEAR(v2.z, 0, MathEngine::epsilon);

    q.a = cosf(MathEngine::PI / 2);
    q.v = MathEngine::Vector3d(0, 1, 0) * sinf(MathEngine::PI / 2);
    v2 = v1.rotate(q);

    EXPECT_NEAR(v2.x, -1, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 0, MathEngine::epsilon);
    EXPECT_NEAR(v2.z, 0, MathEngine::epsilon);

    q.a = cosf(MathEngine::PI);
    q.v = MathEngine::Vector3d(0, 0, 1) * sinf(MathEngine::PI);
    v2 = v1.rotate(q);

    EXPECT_NEAR(v2.x, 1, MathEngine::epsilon);
    EXPECT_NEAR(v2.y, 0, MathEngine::epsilon);
    EXPECT_NEAR(v2.z, 0, MathEngine::epsilon);
}
