#pragma once

#include <cassert>
#include <cmath>

namespace EngineM {

    template <typename T, unsigned int N>
    struct VectorData {
        T data[N];

        VectorData(): data{} {

        }
    };

    template <typename T>
    struct VectorData<T, 2> {
        union {
            T data[2];
            struct {
                T x, y;
            };
        };

        VectorData(): data{} {

        }

        VectorData(T x, T y): data {x, y} {

        }
    };

    template <typename T>
    struct VectorData<T, 3> {
        union {
            T data[3];
            struct {
                T x, y, z;
            };
        };

        VectorData(): data{} {

        }

        VectorData(T x, T y, T z): data {x, y, z} {

        }
    };

    template <typename T>
    struct VectorData<T, 4> {
        union {
            T data[4];
            struct {
                T x, y, z, w;
            };
        };

        VectorData(): data{} {

        }

        VectorData(T x, T y, T z, T w): data {x, y, z, w} {

        }
    };

    template <typename T, unsigned int N>
    class Vector : public VectorData<T, N> {
    public:
        Vector(): VectorData<T, N>() {

        }

        Vector(T x, T y) requires (N == 2): VectorData<T, N>(x, y) {

        }

        Vector(T x, T y, T z) requires (N == 3): VectorData<T, N>(x, y, z) {

        }

        Vector(T x, T y, T z, T w) requires (N == 4): VectorData<T, N>(x, y, z, w) {

        }

        Vector(const Vector<T, N - 1> &v, T a) requires (N > 2) {
            for (int i = 0; i < N - 1; i++) {
                this -> data[i] = v.data[i];
            }
            this -> data[N - 1] = a;
        }

        Vector(const Vector &v) {
            for (int i = 0; i < N; i++) {
                this -> data[i] = v.data[i];
            }
        }

        Vector& operator=(const Vector &v) {
            for (int i = 0; i < N; i++) {
                this -> data[i] = v.data[i];
            }

            return *this;
        }

        T& operator[](unsigned int i) {
            assert(i < N);
            return this -> data[i];
        }
        const T& operator[](unsigned int i) const {
            assert(i < N);
            return this -> data[i];
        }

        [[nodiscard]] Vector operator+(const Vector &v) const {
            Vector out;
            for (int i = 0; i < N; i++) {
                out.data[i] = this -> data[i] + v.data[i];
            }
            return out;
        }

        Vector& operator+=(const Vector &v) {
            for (int i = 0; i < N; i++) {
                this -> data[i] += v.data[i];
            }
            return *this;
        }

        [[nodiscard]] Vector operator-(const Vector &v) const {
            Vector out;
            for (int i = 0; i < N; i++) {
                out.data[i] = this -> data[i] - v.data[i];
            }
            return out;
        }

        Vector& operator-=(const Vector &v) {
            for (int i = 0; i < N; i++) {
                this -> data[i] -= v.data[i];
            }
            return *this;
        }

        [[nodiscard]] Vector operator*(T k) const {
            Vector out;
            for (int i = 0; i < N; i++) {
                out.data[i] = this -> data[i] * k;
            }
            return out;
        }

        Vector& operator*=(T k) {
            for (int i = 0; i < N; i++) {
                this -> data[i] *= k;
            }
            return *this;
        }

        [[nodiscard]] Vector operator/(T k) const {
            Vector out;
            for (int i = 0; i < N; i++) {
                out.data[i] = this -> data[i] / k;
            }
            return out;
        }

        Vector& operator/=(T k) {
            for (int i = 0; i < N; i++) {
                this -> data[i] /= k;
            }
            return *this;
        }

        [[nodiscard]] Vector operator-() const {
            Vector out;
            for (int i = 0; i < N; i++) {
                out.data[i] = -this -> data[i];
            }
            return out;
        }

        [[nodiscard]] T dot(const Vector &v) const {
            T out = 0;
            for (int i = 0; i < N; i++) {
                out += this -> data[i] * v.data[i];
            }
            return out;
        }

        [[nodiscard]] T operator*(const Vector &v) const {
            return dot(v);
        }

        [[nodiscard]] T cross(const Vector &v) const requires (N == 2) {
            return this -> x * v.y - this -> y * v.x;
        }

        [[nodiscard]] T operator^(const Vector &v) const requires (N == 2) {
            return cross(v);
        }

        [[nodiscard]] Vector cross(const Vector &v) const requires (N == 3) {
            return {this -> y * v.z - v.y * this -> z, this -> z * v.x - v.z * this -> x, this -> x * v.y - v.x * this -> y};
        }

        [[nodiscard]] Vector operator^(const Vector &v) const requires (N == 3) {
            return cross(v);
        }

        Vector& operator^=(const Vector &v) requires (N == 3) {
            const float x = this -> y * v.z - v.y * this -> z;
            const float y = this -> z * v.x - v.z * this -> x;
            this -> z = this -> x * v.y - v.x * this -> y;
            this -> x = x;
            this -> y = y;

            return *this;
        }

        bool operator==(const Vector &v) const {
            for (int i = 0; i < N; i++) {
                if (this -> data[i] != v.data[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const Vector &v) const {
            return !(*this == v);
        }

        [[nodiscard]] double magnitude() const {
            double out = 0;

            for (int i = 0; i < N; i++) {
                out += this -> data[i] * this -> data[i];
            }

            return std::sqrt(out);
        }

        Vector& normalise() {
            double mag = magnitude();
            if (mag == 0) {
                return *this;
            }
            for (int i = 0; i < N; i++) {
                this -> data[i] /= mag;
            }
            return *this;
        }

        [[nodiscard]] Vector<T, 2> xy() const requires (N == 3 || N == 4) {
            return { this -> x, this -> y };
        }

        [[nodiscard]] Vector<T, 2> yz() const requires (N == 3 || N == 4) {
            return { this -> y, this -> z };
        }

        [[nodiscard]] Vector<T, 2> xz() const requires (N == 3 || N == 4) {
            Vector<double, 3> t;
            return { this -> x, this -> z };
        }

        [[nodiscard]] Vector<T, 3> xyz() const requires (N == 4) {
            return { this -> x, this -> y, this -> z };
        }

        ~Vector() = default;
    };

    using vec2 = Vector<int, 2>;
    using vec3 = Vector<int, 3>;
    using vec4 = Vector<int, 4>;

    using vec2f = Vector<float, 2>;
    using vec3f = Vector<float, 3>;
    using vec4f = Vector<float, 4>;

    using vec2d = Vector<double, 2>;
    using vec3d = Vector<double, 3>;
    using vec4d = Vector<double, 4>;
}
