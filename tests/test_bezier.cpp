#include <curves/bezier.h>
#include <gtest/gtest.h>

static MathEngine::Vector3d tangentAt(const float t, const MathEngine::Vector3d &p0, const MathEngine::Vector3d &p1, const MathEngine::Vector3d &p2, const MathEngine::Vector3d &p3) {
    const float one_t = 1 - t;
    const float one_t_sq = one_t * one_t;

    return (p1 - p0) * (3 * one_t_sq) + (p2 - p1) * (6 * one_t * t) + (p3 - p2) * (3 * t * t);
}

static MathEngine::Vector3d accelerationAt(const float t, const MathEngine::Vector3d &p0, const MathEngine::Vector3d &p1, const MathEngine::Vector3d &p2, const MathEngine::Vector3d &p3) {
    return (p2 - p1 * 2 + p0) * (6 * (1 - t)) + (p3 - p2 * 2 + p1) * (6 * t);
}

TEST(BezierTest, ParamConstruct1) {
    const MathEngine::BezierCurve curve(3);

    EXPECT_EQ(curve.getDegree(), 3);
    EXPECT_EQ(curve.getPoints().size(), 4);
}

TEST(BezierTest, ParamConstruct2) {
    const std::vector<MathEngine::Vector3d> points(3);
    const MathEngine::BezierCurve curve(2, points);

    EXPECT_EQ(curve.getDegree(), 2);
    EXPECT_EQ(curve.getPoints().size(), 3);
}

TEST(BezierTest, CopyConstruct) {
    std::vector<MathEngine::Vector3d> points;
    points.emplace_back(0, 0, 0);
    points.emplace_back(1, 0, 0);
    points.emplace_back(1, 0, 0);
    const MathEngine::BezierCurve curve1(2, points);

    const MathEngine::BezierCurve curve2(curve1);

    const std::vector<MathEngine::Vector3d> copyPoints = curve2.getPoints();
    EXPECT_EQ(curve2.getDegree(), 2);
    EXPECT_EQ(copyPoints.size(), 3);

    for (int i = 0; i < copyPoints.size(); i++) {
        EXPECT_FLOAT_EQ(copyPoints[i].x, points[i].x);
        EXPECT_FLOAT_EQ(copyPoints[i].y, points[i].y);
        EXPECT_FLOAT_EQ(copyPoints[i].z, points[i].z);
    }
}

TEST(BezierTest, AssignmentOp) {
    std::vector<MathEngine::Vector3d> points;
    points.emplace_back(0, 0, 0);
    points.emplace_back(1, 0, 0);
    points.emplace_back(1, 0, 0);
    const MathEngine::BezierCurve curve1(2, points);

    MathEngine::BezierCurve curve2(3);
    EXPECT_EQ(curve2.getDegree(), 3);
    EXPECT_EQ(curve2.getPoints().size(), 4);

    curve2 = curve1;
    const std::vector<MathEngine::Vector3d> copyPoints = curve2.getPoints();
    EXPECT_EQ(curve2.getDegree(), 2);
    EXPECT_EQ(copyPoints.size(), 3);

    for (int i = 0; i < copyPoints.size(); i++) {
        EXPECT_FLOAT_EQ(copyPoints[i].x, points[i].x);
        EXPECT_FLOAT_EQ(copyPoints[i].y, points[i].y);
        EXPECT_FLOAT_EQ(copyPoints[i].z, points[i].z);
    }
}

TEST(BezierTest, Evaluate) {
    const MathEngine::BezierCurve curve(3, {{0, 0, 0}, {0, 1, 0}, {1, 0, 1}, {0, 0, 1}});

    MathEngine::Vector3d result = curve.evaluate(0);

    EXPECT_FLOAT_EQ(result.x, 0);
    EXPECT_FLOAT_EQ(result.y, 0);
    EXPECT_FLOAT_EQ(result.z, 0);

    result = curve.evaluate(0.5);

    EXPECT_FLOAT_EQ(result.x, 0.375);
    EXPECT_FLOAT_EQ(result.y, 0.375);
    EXPECT_FLOAT_EQ(result.z, 0.5);

    result = curve.evaluate(1);

    EXPECT_FLOAT_EQ(result.x, 0);
    EXPECT_FLOAT_EQ(result.y, 0);
    EXPECT_FLOAT_EQ(result.z, 1);
}

TEST(BezierTest, Tangent) {
    const std::vector<MathEngine::Vector3d> points = {{0, 0, 0}, {0, 1, 0}, {1, 0, 1}, {0, 0, 1}};
    const MathEngine::BezierCurve curve(3, points);

    float t = 0;
    MathEngine::Vector3d result = curve.tangentAt(t);
    MathEngine::Vector3d tangent = tangentAt(t, points[0], points[1], points[2], points[3]);

    EXPECT_FLOAT_EQ(result.x, tangent.x);
    EXPECT_FLOAT_EQ(result.y, tangent.y);
    EXPECT_FLOAT_EQ(result.z, tangent.z);

    t = 0.5;
    result = curve.tangentAt(t);
    tangent = tangentAt(t, points[0], points[1], points[2], points[3]);

    EXPECT_FLOAT_EQ(result.x, tangent.x);
    EXPECT_FLOAT_EQ(result.y, tangent.y);
    EXPECT_FLOAT_EQ(result.z, tangent.z);

    t = 1;
    result = curve.tangentAt(t);
    tangent = tangentAt(t, points[0], points[1], points[2], points[3]);

    EXPECT_FLOAT_EQ(result.x, tangent.x);
    EXPECT_FLOAT_EQ(result.y, tangent.y);
    EXPECT_FLOAT_EQ(result.z, tangent.z);
}

TEST(BezierTest, Acceleration) {
    const std::vector<MathEngine::Vector3d> points = {{0, 0, 0}, {0, 1, 0}, {1, 0, 1}, {0, 0, 1}};
    const MathEngine::BezierCurve curve(3, points);

    float t = 0;

    MathEngine::Vector3d result = curve.accelerationAt(t);
    MathEngine::Vector3d acceleration = accelerationAt(t, points[0], points[1], points[2], points[3]);

    EXPECT_FLOAT_EQ(result.x, acceleration.x);
    EXPECT_FLOAT_EQ(result.y, acceleration.y);
    EXPECT_FLOAT_EQ(result.z, acceleration.z);

    t = 0.5;
    result = curve.accelerationAt(t);
    acceleration = accelerationAt(t, points[0], points[1], points[2], points[3]);

    EXPECT_FLOAT_EQ(result.x, acceleration.x);
    EXPECT_FLOAT_EQ(result.y, acceleration.y);
    EXPECT_FLOAT_EQ(result.z, acceleration.z);

    t = 1;
    result = curve.accelerationAt(t);
    acceleration = accelerationAt(t, points[0], points[1], points[2], points[3]);

    EXPECT_FLOAT_EQ(result.x, acceleration.x);
    EXPECT_FLOAT_EQ(result.y, acceleration.y);
    EXPECT_FLOAT_EQ(result.z, acceleration.z);
}
