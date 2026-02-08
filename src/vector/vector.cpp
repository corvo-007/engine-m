#include "engine-m/vector/vector.h"

#include <cassert>
#include <cmath>

#include "engine-m/utils.h"
#include "engine-m/quaternion/quaternion.h"

namespace EngineM {
    template <typename T, unsigned int N>
    Vector<T, N>::Vector(): VectorData<T, N>() {

    }

    template <typename T, unsigned int N>
    Vector<T, N>::Vector(T x, T y) requires (N == 2): VectorData<T, N>(x, y) {

    }

    template <typename T, unsigned int N>
    Vector<T, N>::Vector(T x, T y, T z) requires (N == 3): VectorData<T, N>(x, y, z) {

    }

    template <typename T, unsigned int N>
    Vector<T, N>::Vector(T x, T y, T z, T w) requires (N == 4): VectorData<T, N>(x, y, z, w) {

    }

    template <typename T, unsigned int N>
    Vector<T, N>::Vector(const Vector &v) {
        for (int i = 0; i < N; i++) {
            this -> data[i] = v.data[i];
        }
    }

    template <typename T, unsigned int N>
    Vector<T, N>& Vector<T, N>::operator=(const Vector &v) {
        for (int i = 0; i < N; i++) {
            this -> data[i] = v.data[i];
        }

        return *this;
    }

    template <typename T, unsigned int N>
    T& Vector<T, N>::operator[](unsigned int i) {
        assert(i >= 0 && i < N);
        return this -> data[i];
    }

    template <typename T, unsigned int N>
    const T& Vector<T, N>::operator[](unsigned int i) const {
        assert(i >= 0 && i < N);
        return this -> data[i];
    }
    
    template <typename T, unsigned int N>
    Vector<T, N> Vector<T, N>::operator+(const Vector &v) const {
        Vector out;
        for (int i = 0; i < N; i++) {
            out.data[i] = this -> data[i] + v.data[i];
        }
        return out;
    }

    template <typename T, unsigned int N>
    Vector<T, N>& Vector<T, N>::operator+=(const Vector &v) {
        for (int i = 0; i < N; i++) {
            this -> data[i] += v.data[i];
        }
        return *this;
    }

    template <typename T, unsigned int N>
    Vector<T, N> Vector<T, N>::operator-(const Vector &v) const {
        Vector out;
        for (int i = 0; i < N; i++) {
            out.data[i] = this -> data[i] - v.data[i];
        }
        return out;
    }

    template <typename T, unsigned int N>
    Vector<T, N>& Vector<T, N>::operator-=(const Vector &v) {
        for (int i = 0; i < N; i++) {
            this -> data[i] -= v.data[i];
        }
        return *this;
    }

    template <typename T, unsigned int N>
    Vector<T, N> Vector<T, N>::operator*(const T k) const {
        Vector out;
        for (int i = 0; i < N; i++) {
            out.data[i] = this -> data[i] * k;
        }
        return out;
    }

    template <typename T, unsigned int N>
    Vector<T, N>& Vector<T, N>::operator*=(const T k) {
        for (int i = 0; i < N; i++) {
            this -> data[i] *= k;
        }
        return *this;
    }

    template <typename T, unsigned int N>
    Vector<T, N> Vector<T, N>::operator/(const T k) const {
        Vector out;
        for (int i = 0; i < N; i++) {
            out.data[i] = this -> data[i] / k;
        }
        return out;
    }

    template <typename T, unsigned int N>
    Vector<T, N>& Vector<T, N>::operator/=(const T k) {
        for (int i = 0; i < N; i++) {
            this -> data[i] /= k;
        }
        return *this;
    }

    template <typename T, unsigned int N>
    Vector<T, N> Vector<T, N>::operator-() const {
        Vector out;
        for (int i = 0; i < N; i++) {
            out.data[i] = -this -> data[i];
        }
        return out;
    }

    template <typename T, unsigned int N>
    T Vector<T, N>::dot(const Vector &v) const {
        T out = 0;
        for (int i = 0; i < N; i++) {
            out += this -> data[i] * v.data[i];
        }
        return out;
    }

    template <typename T, unsigned int N>
    T Vector<T, N>::operator*(const Vector &v) const {
        return dot(v);
    }

    template <typename T, unsigned int N>
    T Vector<T, N>::cross(const Vector &v) const requires (N == 2) {
        return this -> x * v.y - this -> y * v.x;
    }

    template <typename T, unsigned int N>
    T Vector<T, N>::operator^(const Vector &v) const requires (N == 2) {
        return cross(v);
    }

    template <typename T, unsigned int N>
    Vector<T, N> Vector<T, N>::cross(const Vector &v) const requires (N == 3) {
        return {this -> y * v.z - v.y * this -> z, this -> z * v.x - v.z * this -> x, this -> x * v.y - v.x * this -> y};
    }

    template <typename T, unsigned int N>
    Vector<T, N> Vector<T, N>::operator^(const Vector &v) const requires (N == 3) {
        return cross(v);
    }

    template <typename T, unsigned int N>
    Vector<T, N>& Vector<T, N>::operator^=(const Vector &v) requires (N == 3) {
        const float x = this -> y * v.z - v.y * this -> z;
        const float y = this -> z * v.x - v.z * this -> x;
        this -> z = this -> x * v.y - v.x * this -> y;
        this -> x = x;
        this -> y = y;

        return *this;
    }

    template <typename T, unsigned int N>
    bool Vector<T, N>::operator==(const Vector &v) const {
        for (int i = 0; i < N; i++) {
            if (this -> data[i] != v.data[i]) {
                return false;
            }
        }
        return true;
    }

    template <typename T, unsigned int N>
    bool Vector<T, N>::operator!=(const Vector &v) const {
        return !(*this == v);
    }

    template <typename T, unsigned int N>
    double Vector<T, N>::magnitude() const {
        double out = 0;

        for (int i = 0; i < N; i++) {
            out += this -> data[i] * this -> data[i];
        }

        return std::sqrt(out);
    }

    template <typename T, unsigned int N>
    void Vector<T, N>::normalise() {
        double mag = magnitude();
        if (mag == 0) {
            return ;
        }
        for (int i = 0; i < N; i++) {
            this -> data[i] /= mag;
        }
    }

    template <typename T, unsigned int N>
    Vector<T, N> Vector<T, N>::rotate(double angle) const requires (N == 2) {
        return rotateRad(degreesToRadians(angle));
    }

    template <typename T, unsigned int N>
    Vector<T, N> Vector<T, N>::rotateRad(double radians) const requires (N == 2) {
        return {static_cast<T>(cosf(radians) * this -> x - sinf(radians) * this -> y), static_cast<T>(sinf(radians) * this -> x + cosf(radians) * this -> y)};
    }

    template <typename T, unsigned int N>
    Vector<T, N> Vector<T, N>::rotate(double angle, const Vector &axis) const requires (N == 3) {
        return rotateRad(degreesToRadians(angle), axis);
    }

    template <typename T, unsigned int N>
    Vector<T, N> Vector<T, N>::rotateRad(double radians, const Vector &axis) const requires (N == 3) {
        vec3f n_axis = {static_cast<float>(axis.x), static_cast<float>(axis.y), static_cast<float>(axis.z)};
        n_axis.normalise();

        radians /= 2;

        const Quaternion q(cosf(radians), n_axis * sinf(radians));
        return rotate(q);
    }

    template <typename T, unsigned int N>
    Vector<T, N> Vector<T, N>::rotate(const Quaternion &q) const requires (N == 3) {
        vec3f v = {static_cast<float>(this -> x), static_cast<float>(this -> y), static_cast<float>(this -> z)};
        const Quaternion p(0, v);
        const Quaternion q_inv = q.inverse();

        const Quaternion rotation = q * p * q_inv;

        return {static_cast<T>(rotation.v.x), static_cast<T>(rotation.v.y), static_cast<T>(rotation.v.z)};
    }

    template class Vector<int, 2>;
    template class Vector<int, 3>;
    template class Vector<int, 4>;

    template class Vector<float, 2>;
    template class Vector<float, 3>;
    template class Vector<float, 4>;

    template class Vector<double, 2>;
    template class Vector<double, 3>;
    template class Vector<double, 4>;
}
