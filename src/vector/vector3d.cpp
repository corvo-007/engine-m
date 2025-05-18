#include <cmath>
#include "engine-m/vector/vector3d.h"
#include "engine-m/quaternion/quaternion.h"
#include "engine-m/utils.h"

namespace EngineM {

    Vector3d::Vector3d(const float x, const float y, const float z): x(x), y(y), z(z) {

    }

    Vector3d Vector3d::operator+(const Vector3d &v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vector3d& Vector3d::operator+=(const Vector3d &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3d Vector3d::operator-(const Vector3d &v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    Vector3d& Vector3d::operator-=(const Vector3d &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3d Vector3d::operator*(const float k) const {
        return {x * k, y * k, z * k};
    }

    Vector3d& Vector3d::operator*=(const float k) {
        x *= k;
        y *= k;
        z *= k;
        return *this;
    }

    Vector3d Vector3d::operator/(const float k) const {
        return {x / k, y / k, z / k};
    }

    Vector3d& Vector3d::operator/=(const float k) {
        x /= k;
        y /= k;
        z /= k;
        return *this;
    }

    Vector3d Vector3d::operator-() const {
        return {-x, -y, -z};
    }

    float Vector3d::dot(const Vector3d &v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    float Vector3d::operator*(const Vector3d &v) const {
        return dot(v);
    }

    Vector3d Vector3d::cross(const Vector3d &v) const {
        return {y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y};
    }

    Vector3d Vector3d::operator^(const Vector3d &v) const {
        return cross(v);
    }

    Vector3d& Vector3d::operator^=(const Vector3d &v) {
        const float x = this -> y * v.z - v.y * this -> z;
        const float y = this -> z * v.x - v.z * this -> x;
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
        return std::sqrt(x * x + y * y + z * z);
    }

    void Vector3d::normalise() {
        const float mag = magnitude();

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

        const Quaternion q(cosf(radians), n_axis * sinf(radians));
        return rotate(q);
    }

    Vector3d Vector3d::rotate(const Quaternion &q) const {
        const Quaternion p(0, *this);
        const Quaternion q_inv = q.inverse();

        const Quaternion rotation = q * p * q_inv;

        return rotation.v;
    }
}