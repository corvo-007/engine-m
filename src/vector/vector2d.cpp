#include <cmath>
#include "engine-m/vector/vector2d.h"
#include "engine-m/utils.h"

namespace EngineM {

    Vector2d::Vector2d(const float x, const float y): x(x), y(y) {

    }

    Vector2d Vector2d::operator+(const Vector2d &v) const {
        return {x + v.x, y + v.y};
    }

    Vector2d& Vector2d::operator+=(const Vector2d &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2d Vector2d::operator-(const Vector2d &v) const {
        return {x - v.x, y - v.y};
    }

    Vector2d& Vector2d::operator-=(const Vector2d &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2d Vector2d::operator*(const float k) const {
        return {x * k, y * k};
    }

    Vector2d& Vector2d::operator*=(const float k) {
        x *= k;
        y *= k;
        return *this;
    }

    Vector2d Vector2d::operator/(const float k) const {
        return {x / k, y / k};
    }

    Vector2d& Vector2d::operator/=(const float k) {
        x /= k;
        y /= k;
        return *this;
    }

    Vector2d Vector2d::operator-() const {
        return {-x, -y};
    }

    float Vector2d::dot(const Vector2d &v) const {
        return x * v.x + y * v.y;
    }

    float Vector2d::operator*(const Vector2d &v) const {
        return dot(v);
    }

    float Vector2d::cross(const Vector2d &v) const {
        return x * v.y - y * v.x;
    }

    float Vector2d::operator^(const Vector2d &v) const {
        return cross(v);
    }

    bool Vector2d::operator==(const Vector2d &v) const {
        return equals(x, v.x) && equals(y, v.y);
    }

    bool Vector2d::operator!=(const Vector2d &v) const {
        return !(*this == v);
    }

    float Vector2d::magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    void Vector2d::normalise() {
        const float mag = magnitude();

        x /= mag;
        y /= mag;
    }

    Vector2d Vector2d::rotate(const float angle) const {
        return rotateRad(degreesToRadians(angle));
    }

    Vector2d Vector2d::rotateRad(const float radians) const {
        return {cosf(radians) * x - sinf(radians) * y, sinf(radians) * x + cosf(radians) * y};
    }
}