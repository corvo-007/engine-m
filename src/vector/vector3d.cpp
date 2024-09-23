#include <cmath>
#include "vector/vector3d.h"
#include "quaternion/quaternion.h"
#include "constants.h"
#include "utils.h"

namespace MathEngine {

    Vector3d::Vector3d(): x(0), y(0), z(0) {

    }

    Vector3d::Vector3d(float x, float y, float z): x(x), y(y), z(z) {

    }

    Vector3d::Vector3d(const Vector3d &v): x(v.x), y(v.y), z(v.z) {

    }

    Vector3d& Vector3d::operator=(const Vector3d &v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    Vector3d Vector3d::operator+(const Vector3d &v) const {
        return Vector3d(x + v.x, y + v.y, z + v.z);
    }

    Vector3d& Vector3d::operator+=(const Vector3d &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3d Vector3d::operator-(const Vector3d &v) const {
        return Vector3d(x - v.x, y - v.y, z - v.z);
    }

    Vector3d& Vector3d::operator-=(const Vector3d &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3d Vector3d::operator*(const float k) const {
        return Vector3d(x * k, y * k, z * k);
    }

    Vector3d& Vector3d::operator*=(const float k) {
        x *= k;
        y *= k;
        z *= k;
        return *this;
    }

    Vector3d Vector3d::operator/(const float k) const {
        return Vector3d(x / k, y / k, z / k);
    }

    Vector3d& Vector3d::operator/=(const float k) {
        x /= k;
        y /= k;
        z /= k;
        return *this;
    }

    float Vector3d::dot(const Vector3d &v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    float Vector3d::operator*(const Vector3d &v) const {
        return dot(v);
    }

    Vector3d Vector3d::cross(const Vector3d &v) const {
        return Vector3d(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y);
    }

    Vector3d Vector3d::operator^(const Vector3d &v) const {
        return cross(v);
    }

    Vector3d& Vector3d::operator^=(const Vector3d &v) {
        int x = this -> y * v.z - v.y * this -> z;
        int y = this -> z * v.x - v.z * this -> x;
        z = this -> x * v.y - v.x * this -> y;
        this -> x = x;
        this -> y = y;

        return *this;
    }

    bool Vector3d::operator==(const Vector3d &v) const {
        return equals(x, v.x) && equals(y, v.y) && equals(z, v.z);
    }

    bool Vector3d::operator!=(const Vector3d &v) const {
        return !((*this) == v);
    }

    float Vector3d::magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }

    void Vector3d::normalise() {
        float mag = magnitude();

        x /= mag;
        y /= mag;
        z /= mag;
    }

    Vector3d Vector3d::rotate(const float angle, const Vector3d &axis) const {
        return rotateRad(degreesToRadians(angle), axis);
    }

    Vector3d Vector3d::rotateRad(float radians, const Vector3d &axis) const {
        Vector3d n_axis = axis;
        n_axis.normalise();

        radians /= 2;

        Quaternion q(cosf(radians), n_axis * sinf(radians));
        return rotate(q);
    }

    Vector3d Vector3d::rotate(const Quaternion &q) const {
        Quaternion p(0, *this);
        Quaternion q_inv = q.inverse();

        Quaternion rotation = q * p * q_inv;

        return rotation.v;
    }
}