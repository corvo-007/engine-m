#include <cmath>
#include "vector2d.h"

namespace MathEngine {

    Vector2d::Vector2d(): x(0), y(0) {

    }

    Vector2d::Vector2d(float x, float y): x(x), y(y) {

    }

    Vector2d::Vector2d(const Vector2d &v): x(v.x), y(v.y) {

    }

    Vector2d& Vector2d::operator=(const Vector2d &v) {
        x = v.x;
        y = v.y;
        return *this;
    }

    Vector2d Vector2d::operator+(const Vector2d &v) const {
        return Vector2d(x + v.x, y + v.y);
    }

    Vector2d& Vector2d::operator+=(const Vector2d &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2d Vector2d::operator-(const Vector2d &v) const {
        return Vector2d(x - v.x, y - v.y);
    }

    Vector2d& Vector2d::operator-=(const Vector2d &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2d Vector2d::operator*(const float k) const {
        return Vector2d(x * k, y * k);
    }

    Vector2d& Vector2d::operator*=(const float k) {
        x *= k;
        y *= k;
        return *this;
    }

    Vector2d Vector2d::operator/(const float k) const {
        return Vector2d(x / k, y / k);
    }

    Vector2d& Vector2d::operator/=(const float k) {
        x /= k;
        y /= k;
        return *this;
    }

    float Vector2d::dot(const Vector2d &v) const {
        return x * v.x + y * v.y;
    }

    float Vector2d::operator*(const Vector2d &v) const {
        return dot(v);
    }

    Vector3d Vector2d::cross(const Vector2d &v) const {
        return Vector3d(0, 0, x * v.y - y * v.x);
    }

    Vector3d Vector2d::operator^(const Vector2d &v) const {
        return cross(v);
    }

    float Vector2d::magnitude() const {
        return sqrt(x * x + y * y);
    }

    float Vector2d::operator+() const {
        return magnitude();
    }

    void Vector2d::normalise() {
        float mag = +(*this);

        x /= mag;
        y /= mag;
    }
}