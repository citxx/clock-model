#include <cmath>
#include <iomanip>

#include "Vector3D.hpp"

Vector3D::Vector3D(float x, float y, float z):
        x(x),
        y(y),
        z(z) {
}

Vector3D::Vector3D(const Vector3D &a):
        x(a.x),
        y(a.y),
        z(a.z) {
}

float Vector3D::len() const {
    return sqrtf((*this) * (*this));
}

bool operator ==(const Vector3D &a, const Vector3D &b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool operator !=(const Vector3D &a, const Vector3D &b){
    return a.x != b.x || a.y != b.y || a.z != b.z;
}

Vector3D operator -(const Vector3D &a) {
    return Vector3D(a.x, a.y, a.z);
}

Vector3D operator +(const Vector3D &a, const Vector3D &b) {
    return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3D operator -(const Vector3D &a, const Vector3D &b) {
    return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

float operator *(const Vector3D &a, const Vector3D &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3D operator *(float a, const Vector3D &b) {
    return Vector3D(a * b.x, a * b.y, a * b.z);
}

Vector3D operator *(const Vector3D &b, float a) {
    return Vector3D(a * b.x, a * b.y, a * b.z);
}

Vector3D operator /(const Vector3D &a, float b) {
    return Vector3D(a.x / b, a.y / b, a.z / b);
}

Vector3D normalized(const Vector3D &a) {
    return a / a.len();
}

Vector3D crossProduct(const Vector3D &a, const Vector3D &b) {
    return Vector3D(a.y * b.z - a.z * b.y, -a.x * b.z + a.z * b.x, a.x * b.y - a.y * b.x);
}

Vector3D normal(const Vector3D &a, const Vector3D &b) {
    return normalized(crossProduct(a, b));
}

float angle(const Vector3D &a, const Vector3D &b) {
    return atan2f(crossProduct(a, b).len(), a * b);
}

std::ostream & operator <<(std::ostream &stream, const Vector3D &a) {
    stream << std::setprecision(2) << "(" << a.x << ", " << a.y << ", " << a.z << ")";
    return stream;
}
