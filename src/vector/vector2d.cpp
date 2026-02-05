#include <cmath>
#include "engine-m/vector/vector2d.h"
#include "engine-m/utils.h"

namespace EngineM {

    template <typename T>
    Vector2d<T>::Vector2d(const T x, const T y): x(x), y(y) {

    }

    template <typename T>
    Vector2d<T> Vector2d<T>::operator+(const Vector2d &v) const {
        return {x + v.x, y + v.y};
    }

    template <typename T>
    Vector2d<T>& Vector2d<T>::operator+=(const Vector2d &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    template <typename T>
    Vector2d<T> Vector2d<T>::operator-(const Vector2d &v) const {
        return {x - v.x, y - v.y};
    }

    template <typename T>
    Vector2d<T>& Vector2d<T>::operator-=(const Vector2d &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    template <typename T>
    Vector2d<T> Vector2d<T>::operator*(const T k) const {
        return {x * k, y * k};
    }

    template <typename T>
    Vector2d<T>& Vector2d<T>::operator*=(const T k) {
        x *= k;
        y *= k;
        return *this;
    }

    template <typename T>
    Vector2d<T> Vector2d<T>::operator/(const T k) const {
        return {x / k, y / k};
    }

    template <typename T>
    Vector2d<T>& Vector2d<T>::operator/=(const T k) {
        x /= k;
        y /= k;
        return *this;
    }

    template <typename T>
    Vector2d<T> Vector2d<T>::operator-() const {
        return {-x, -y};
    }

    template <typename T>
    T Vector2d<T>::dot(const Vector2d &v) const {
        return x * v.x + y * v.y;
    }

    template <typename T>
    T Vector2d<T>::operator*(const Vector2d &v) const {
        return dot(v);
    }

    template <typename T>
    T Vector2d<T>::cross(const Vector2d &v) const {
        return x * v.y - y * v.x;
    }

    template <typename T>
    T Vector2d<T>::operator^(const Vector2d &v) const {
        return cross(v);
    }

    template <typename T>
    bool Vector2d<T>::operator==(const Vector2d &v) const {
        return equals(x, v.x) && equals(y, v.y);
    }

    template <typename T>
    bool Vector2d<T>::operator!=(const Vector2d &v) const {
        return !(*this == v);
    }

    template <typename T>
    float Vector2d<T>::magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    template <typename T>
    void Vector2d<T>::normalise() {
        const float mag = magnitude();

        if (mag == T{}) {
            return;
        }

        x /= mag;
        y /= mag;
    }

    template <typename T>
    Vector2d<float> Vector2d<T>::rotate(const float angle) const {
        return rotateRad(degreesToRadians(angle));
    }

    template <typename T>
    Vector2d<float> Vector2d<T>::rotateRad(const float radians) const {
        return {cosf(radians) * x - sinf(radians) * y, sinf(radians) * x + cosf(radians) * y};
    }

    template class ENGINE_M_API Vector2d<int>;
    template class ENGINE_M_API Vector2d<float>;
}