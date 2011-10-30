#include <ostream>

#include "Quaternion.hpp"

Quaternion::Quaternion(float w, const Vector &v):
        w(w),
        v(v) {
}

Quaternion::Quaternion(float w, float x, float y, float z):
        w(w),
        v(Vector(x, y, z)) {
}

bool operator ==(const Quaternion &a, const Quaternion &b) {
    return a.w == b.w && a.v == b.v;
}

bool operator !=(const Quaternion &a, const Quaternion &b) {
    return a.w != b.w || a.v != b.v;
}

Quaternion operator -(const Quaternion &a) {
    return Quaternion(-a.w, -a.v);
}

Quaternion operator +(const Quaternion &a, const Quaternion &b) {
    return Quaternion(a.w + b.w, a.v + b.v);
}

Quaternion operator -(const Quaternion &a, const Quaternion &b) {
    return Quaternion(a.w - b.w, a.v - b.v);
}

Quaternion operator *(const Quaternion &a, const Quaternion &b) {
    return Quaternion(a.w * b.w - a.v * b.v, a.w * b.v + b.w * a.v + multiply(a.v, b.v));
}

Quaternion operator *(float a, const Quaternion &b) {
    return Quaternion(a * b.w, a * b.v);
}

Quaternion operator *(Quaternion &b, float a) {
    return Quaternion(a * b.w, a * b.v);
}

Quaternion normalized(const Quaternion &a) {
    float l = a.w * a.w + a.v * a.v;
    return Quaternion(a.w / l, a.v / l);
}

std::ostream & operator <<(std::ostream &stream, const Quaternion &a) {
    stream << "[" << a.w << ", " << a.v << "]";
    return stream;
}
