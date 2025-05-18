#include <cmath>
#include "engine-m/quaternion/quaternion.h"
#include "engine-m/utils.h"

namespace EngineM {

    Quaternion::Quaternion(const float a, const Vector3d &v): a(a), v(v) {

    }

    Quaternion Quaternion::operator+(const Quaternion &q) const {
        return {a + q.a, v + q.v};
    }

    Quaternion& Quaternion::operator+=(const Quaternion &q) {
        a += q.a;
        v += q.v;
        return *this;
    }

    Quaternion Quaternion::operator-(const Quaternion &q) const {
        return {a - q.a, v - q.v};
    }

    Quaternion& Quaternion::operator-=(const Quaternion &q) {
        a -= q.a;
        v -= q.v;
        return *this;
    }

    Quaternion Quaternion::operator*(const Quaternion &q) const {
        return {a * q.a - v * q.v, v * q.a + q.v * a + (v ^ q.v)};
    }

    Quaternion& Quaternion::operator*=(const Quaternion &q) {
        float a = this -> a * q.a - v * q.v;
        v = v * q.a + q.v * this -> a + (v ^ q.v);
        this -> a = a;
        return *this;
    }

    Quaternion Quaternion::operator*(const float k) const {
        return {a * k, v * k};
    }

    Quaternion& Quaternion::operator*=(const float k) {
        a *= k;
        v *= k;
        return *this;
    }

    Quaternion Quaternion::operator/(const float k) const {
        return {a / k, v / k};
    }

    Quaternion& Quaternion::operator/=(const float k) {
        a /= k;
        v /= k;
        return *this;
    }

    bool Quaternion::operator==(const Quaternion &q) const {
        return equals(a, q.a) && v == q.v;
    }

    bool Quaternion::operator!=(const Quaternion &q) const {
        return !(*this == q);
    }

    float Quaternion::norm() const {
        return std::sqrt(a * a + v * v);
    }

    void Quaternion::normalise() {
        const float n = norm();
        if (n == 0) {
            return ;
        }
        a /= n;
        v /= n;
    }

    Quaternion Quaternion::conjugate() const {
        return {a, v * -1};
    }

    Quaternion Quaternion::inverse() const {
        Quaternion conj = conjugate();
        const float n = norm();
        return conj /= (n * n);
    }
}
