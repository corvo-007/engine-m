#include <curve/hermite.h>
#include <gtest/gtest.h>

static MathEngine::Vector3d tangentAt(const float t, const MathEngine::Vector3d &p1, const MathEngine::Vector3d &p2, const MathEngine::Vector3d &v1, const MathEngine::Vector3d &v2) {
    const float tt = t * t;
    const float temp = 6 * (tt - t);

    return p1 * temp + v1 * (3 * tt - 4 * t + 1) - p2 * temp + v2 * (3 * tt - 2 * t);
}

static MathEngine::Vector3d accelerationAt(const float t, const MathEngine::Vector3d &p1, const MathEngine::Vector3d &p2, const MathEngine::Vector3d &v1, const MathEngine::Vector3d &v2) {
    return p1 * 6 * (2 * t - 1) + v1 * (6 * t - 4) - p2 * 6 * (2 * t - 1) + v2 * (6 * t - 2);
}

TEST(HermiteTest, DefaultConstruct) {
    const MathEngine::HermiteCurve curve;

    auto [ p1, p2 ] = curve.getPoints();
    auto [ v1, v2 ] = curve.getTangents();

    EXPECT_FLOAT_EQ(p1.x, 0);
    EXPECT_FLOAT_EQ(p1.y, 0);
    EXPECT_FLOAT_EQ(p1.z, 0);
    EXPECT_FLOAT_EQ(p2.x, 0);
    EXPECT_FLOAT_EQ(p2.y, 0);
    EXPECT_FLOAT_EQ(p2.z, 0);
    EXPECT_FLOAT_EQ(v1.x, 0);
    EXPECT_FLOAT_EQ(v1.y, 0);
    EXPECT_FLOAT_EQ(v1.z, 0);
    EXPECT_FLOAT_EQ(v2.x, 0);
    EXPECT_FLOAT_EQ(v2.y, 0);
    EXPECT_FLOAT_EQ(v2.z, 0);
}

TEST(HermiteTest, ParamConstruct) {
    const MathEngine::HermiteCurve curve({1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12});

    auto [p1, p2] = curve.getPoints();
    auto [v1, v2] = curve.getTangents();

    EXPECT_FLOAT_EQ(p1.x, 1);
    EXPECT_FLOAT_EQ(p1.y, 2);
    EXPECT_FLOAT_EQ(p1.z, 3);
    EXPECT_FLOAT_EQ(p2.x, 4);
    EXPECT_FLOAT_EQ(p2.y, 5);
    EXPECT_FLOAT_EQ(p2.z, 6);
    EXPECT_FLOAT_EQ(v1.x, 7);
    EXPECT_FLOAT_EQ(v1.y, 8);
    EXPECT_FLOAT_EQ(v1.z, 9);
    EXPECT_FLOAT_EQ(v2.x, 10);
    EXPECT_FLOAT_EQ(v2.y, 11);
    EXPECT_FLOAT_EQ(v2.z, 12);

}

TEST(HermiteTest, CopyConstruct) {
    const MathEngine::Vector3d p1(1, 2, 3);
    const MathEngine::Vector3d p2(4, 5, 6);
    const MathEngine::Vector3d v1(7, 8, 9);
    const MathEngine::Vector3d v2(10, 11, 12);
    const MathEngine::HermiteCurve curve1(p1, p2, v1, v2);

    const MathEngine::HermiteCurve curve2(curve1);

    auto [ copy_p1, copy_p2 ] = curve2.getPoints();
    auto [ copy_v1, copy_v2 ] = curve2.getTangents();

    EXPECT_FLOAT_EQ(p1.x, copy_p1.x);
    EXPECT_FLOAT_EQ(p1.y, copy_p1.y);
    EXPECT_FLOAT_EQ(p1.z, copy_p1.z);
    EXPECT_FLOAT_EQ(p2.x, copy_p2.x);
    EXPECT_FLOAT_EQ(p2.y, copy_p2.y);
    EXPECT_FLOAT_EQ(p2.z, copy_p2.z);
    EXPECT_FLOAT_EQ(v1.x, copy_v1.x);
    EXPECT_FLOAT_EQ(v1.y, copy_v1.y);
    EXPECT_FLOAT_EQ(v1.z, copy_v1.z);
    EXPECT_FLOAT_EQ(v2.x, copy_v2.x);
    EXPECT_FLOAT_EQ(v2.y, copy_v2.y);
    EXPECT_FLOAT_EQ(v2.z, copy_v2.z);
}

TEST(HermiteTest, AssignmentOp) {
    const MathEngine::Vector3d p1(1, 2, 3);
    const MathEngine::Vector3d p2(4, 5, 6);
    const MathEngine::Vector3d v1(7, 8, 9);
    const MathEngine::Vector3d v2(10, 11, 12);
    const MathEngine::HermiteCurve curve1(p1, p2, v1, v2);

    MathEngine::HermiteCurve curve2;

    auto [ copy_p1, copy_p2 ] = curve2.getPoints();
    auto [ copy_v1, copy_v2 ] = curve2.getTangents();

    EXPECT_EQ(copy_p1.x, 0);
    EXPECT_EQ(copy_p1.y, 0);
    EXPECT_EQ(copy_p1.z, 0);
    EXPECT_EQ(copy_p2.x, 0);
    EXPECT_EQ(copy_p2.y, 0);
    EXPECT_EQ(copy_p2.z, 0);
    EXPECT_EQ(copy_v1.x, 0);
    EXPECT_EQ(copy_v1.y, 0);
    EXPECT_EQ(copy_v1.z, 0);
    EXPECT_EQ(copy_v2.x, 0);
    EXPECT_EQ(copy_v2.y, 0);
    EXPECT_EQ(copy_v2.z, 0);

    curve2 = curve1;
    copy_p1 = curve2.getStart();
    copy_p2 = curve2.getEnd();
    copy_v1 = curve2.getStartTangent();
    copy_v2 = curve2.getEndTangent();

    EXPECT_FLOAT_EQ(p1.x, copy_p1.x);
    EXPECT_FLOAT_EQ(p1.y, copy_p1.y);
    EXPECT_FLOAT_EQ(p1.z, copy_p1.z);
    EXPECT_FLOAT_EQ(p2.x, copy_p2.x);
    EXPECT_FLOAT_EQ(p2.y, copy_p2.y);
    EXPECT_FLOAT_EQ(p2.z, copy_p2.z);
    EXPECT_FLOAT_EQ(v1.x, copy_v1.x);
    EXPECT_FLOAT_EQ(v1.y, copy_v1.y);
    EXPECT_FLOAT_EQ(v1.z, copy_v1.z);
    EXPECT_FLOAT_EQ(v2.x, copy_v2.x);
    EXPECT_FLOAT_EQ(v2.y, copy_v2.y);
    EXPECT_FLOAT_EQ(v2.z, copy_v2.z);
}

TEST(HermiteTest, Evaluate) {
    const MathEngine::Vector3d p1;
    const MathEngine::Vector3d p2(5, 0, 0);
    const MathEngine::Vector3d v1(0, 5, 0);
    const MathEngine::Vector3d v2(0, -5, 0);
    const MathEngine::HermiteCurve curve(p1, p2, v1, v2);

    MathEngine::Vector3d result = curve.evaluate(0);

    EXPECT_FLOAT_EQ(result.x, p1.x);
    EXPECT_FLOAT_EQ(result.y, p1.y);
    EXPECT_FLOAT_EQ(result.z, p1.z);

    result = curve.evaluate(0.5);

    EXPECT_FLOAT_EQ(result.x, 2.5);
    EXPECT_FLOAT_EQ(result.y, 1.25);
    EXPECT_FLOAT_EQ(result.z, 0);

    result = curve.evaluate(1);

    EXPECT_FLOAT_EQ(result.x, p2.x);
    EXPECT_FLOAT_EQ(result.y, p2.y);
    EXPECT_FLOAT_EQ(result.z, p2.z);
}

TEST(HermiteTest, Tangent) {
    const MathEngine::Vector3d p1;
    const MathEngine::Vector3d p2(5, 0, 0);
    const MathEngine::Vector3d v1(0, 5, 0);
    const MathEngine::Vector3d v2(0, -5, 0);
    const MathEngine::HermiteCurve curve(p1, p2, v1, v2);

    float t = 0;
    MathEngine::Vector3d result = curve.tangentAt(t);

    EXPECT_FLOAT_EQ(result.x, v1.x);
    EXPECT_FLOAT_EQ(result.y, v1.y);
    EXPECT_FLOAT_EQ(result.z, v1.z);

    t = 0.5;
    result = curve.tangentAt(t);
    const MathEngine::Vector3d tangent = tangentAt(t, p1, p2, v1, v2);

    EXPECT_FLOAT_EQ(result.x, tangent.x);
    EXPECT_FLOAT_EQ(result.y, tangent.y);
    EXPECT_FLOAT_EQ(result.z, tangent.z);

    t = 1;
    result = curve.tangentAt(t);

    EXPECT_FLOAT_EQ(result.x, v2.x);
    EXPECT_FLOAT_EQ(result.y, v2.y);
    EXPECT_FLOAT_EQ(result.z, v2.z);
}

TEST(HermiteTest, Acceleration) {
    const MathEngine::Vector3d p1;
    const MathEngine::Vector3d p2(5, 0, 0);
    const MathEngine::Vector3d v1(0, 5, 0);
    const MathEngine::Vector3d v2(0, -5, 0);
    const MathEngine::HermiteCurve curve(p1, p2, v1, v2);

    float t = 0;

    MathEngine::Vector3d result = curve.accelerationAt(t);
    MathEngine::Vector3d acceleration = accelerationAt(t, p1, p2, v1, v2);

    EXPECT_FLOAT_EQ(result.x, acceleration.x);
    EXPECT_FLOAT_EQ(result.y, acceleration.y);
    EXPECT_FLOAT_EQ(result.z, acceleration.z);

    t = 0.5;
    result = curve.accelerationAt(t);
    acceleration = accelerationAt(t, p1, p2, v1, v2);

    EXPECT_FLOAT_EQ(result.x, acceleration.x);
    EXPECT_FLOAT_EQ(result.y, acceleration.y);
    EXPECT_FLOAT_EQ(result.z, acceleration.z);

    t = 1;
    result = curve.accelerationAt(t);
    acceleration = accelerationAt(t, p1, p2, v1, v2);

    EXPECT_FLOAT_EQ(result.x, acceleration.x);
    EXPECT_FLOAT_EQ(result.y, acceleration.y);
    EXPECT_FLOAT_EQ(result.z, acceleration.z);
}
