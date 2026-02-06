#include <cmath>
#include "engine-m/vector/vector3d.h"

#include <cassert>

#include "engine-m/quaternion/quaternion.h"
#include "engine-m/utils.h"

namespace EngineM {

    template <typename T>
    Vector3d<T>::Vector3d(): data{} {

    }

    template <typename T>
    Vector3d<T>::Vector3d(const T x, const T y, const T z): x(x), y(y), z(z) {

    }

    template <typename T>
    T& Vector3d<T>::operator[](const int i) {
        assert(i >= 0 && i < 3);
        return data[i];
    }

    template <typename T>
    const T& Vector3d<T>::operator[](const int i) const {
        assert(i >= 0 && i < 3);
        return data[i];
    }

    template <typename T>
    Vector3d<T> Vector3d<T>::operator+(const Vector3d &v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    template <typename T>
    Vector3d<T>& Vector3d<T>::operator+=(const Vector3d &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    template <typename T>
    Vector3d<T> Vector3d<T>::operator-(const Vector3d &v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    template <typename T>
    Vector3d<T>& Vector3d<T>::operator-=(const Vector3d &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    template <typename T>
    Vector3d<T> Vector3d<T>::operator*(const T k) const {
        return {x * k, y * k, z * k};
    }

    template <typename T>
    Vector3d<T>& Vector3d<T>::operator*=(const T k) {
        x *= k;
        y *= k;
        z *= k;
        return *this;
    }

    template <typename T>
    Vector3d<T> Vector3d<T>::operator/(const T k) const {
        return {x / k, y / k, z / k};
    }

    template <typename T>
    Vector3d<T>& Vector3d<T>::operator/=(const T k) {
        x /= k;
        y /= k;
        z /= k;
        return *this;
    }

    template <typename T>
    Vector3d<T> Vector3d<T>::operator-() const {
        return {-x, -y, -z};
    }

    template <typename T>
    T Vector3d<T>::dot(const Vector3d &v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    template <typename T>
    T Vector3d<T>::operator*(const Vector3d &v) const {
        return dot(v);
    }

    template <typename T>
    Vector3d<T> Vector3d<T>::cross(const Vector3d &v) const {
        return {y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y};
    }

    template <typename T>
    Vector3d<T> Vector3d<T>::operator^(const Vector3d &v) const {
        return cross(v);
    }

    template <typename T>
    Vector3d<T>& Vector3d<T>::operator^=(const Vector3d &v) {
        const float x = this -> y * v.z - v.y * this -> z;
        const float y = this -> z * v.x - v.z * this -> x;
        z = this -> x * v.y - v.x * this -> y;
        this -> x = x;
        this -> y = y;

        return *this;
    }

    template <typename T>
    bool Vector3d<T>::operator==(const Vector3d &v) const {
        return equals(x, v.x) && equals(y, v.y) && equals(z, v.z);
    }

    template <typename T>
    bool Vector3d<T>::operator!=(const Vector3d &v) const {
        return !((*this) == v);
    }

    template <typename T>
    float Vector3d<T>::magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    template <typename T>
    void Vector3d<T>::normalise() {
        const float mag = magnitude();

        if (mag == T{}) {
            return;
        }

        x /= mag;
        y /= mag;
        z /= mag;
    }

    template <typename T>
    Vector3d<float> Vector3d<T>::rotate(const float angle, const Vector3d &axis) const {
        return rotateRad(degreesToRadians(angle), axis);
    }

    template <typename T>
    Vector3d<float> Vector3d<T>::rotateRad(float radians, const Vector3d &axis) const {
        vec3f n_axis = {static_cast<float>(axis.x), static_cast<float>(axis.y), static_cast<float>(axis.z)};
        n_axis.normalise();

        radians /= 2;

        const Quaternion q(cosf(radians), n_axis * sinf(radians));
        return rotate(q);
    }

    template <typename T>
    Vector3d<float> Vector3d<T>::rotate(const Quaternion &q) const {
        vec3f v = {static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)};
        const Quaternion p(0, v);
        const Quaternion q_inv = q.inverse();

        const Quaternion rotation = q * p * q_inv;

        return rotation.v;
    }

    template class ENGINE_M_API Vector3d<int>;
    template class ENGINE_M_API Vector3d<float>;
}