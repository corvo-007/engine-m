#pragma once

namespace EngineM {
    class Quaternion;

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
        Vector();

        Vector(T x, T y) requires (N == 2);
        Vector(T x, T y, T z) requires (N == 3);
        Vector(T x, T y, T z, T w) requires (N == 4);

        Vector(const Vector &v);

        Vector& operator=(const Vector &v);

        T& operator[](unsigned int i);
        const T& operator[](unsigned int i) const;

        [[nodiscard]] Vector operator+(const Vector &v) const;
        Vector& operator+=(const Vector &v);

        [[nodiscard]] Vector operator-(const Vector &v) const;
        Vector& operator-=(const Vector &v);

        [[nodiscard]] Vector operator*(T k) const;
        Vector& operator*=(T k);

        [[nodiscard]] Vector operator/(T k) const;
        Vector& operator/=(T k);

        [[nodiscard]] Vector operator-() const;

        [[nodiscard]] T dot(const Vector &v) const;
        [[nodiscard]] T operator*(const Vector &v) const;

        [[nodiscard]] T cross(const Vector &v) const requires (N == 2);
        [[nodiscard]] T operator^(const Vector &v) const requires (N == 2);

        [[nodiscard]] Vector cross(const Vector &v) const requires (N == 3);
        [[nodiscard]] Vector operator^(const Vector &v) const requires (N == 3);
        Vector& operator^=(const Vector &) requires (N == 3);

        bool operator==(const Vector &v) const;
        bool operator!=(const Vector &v) const;

        [[nodiscard]] double magnitude() const;

        void normalise();

        [[nodiscard]] Vector rotate(double angle) const requires (N == 2);
        [[nodiscard]] Vector rotateRad(double radians) const requires (N == 2);

        [[nodiscard]] Vector rotate(double angle, const Vector &axis) const requires (N == 3);
        [[nodiscard]] Vector rotateRad(double radians, const Vector &axis) const requires (N == 3);
        [[nodiscard]] Vector rotate(const Quaternion &q) const requires (N == 3);

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
