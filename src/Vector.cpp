#include <cmath>
#include <iomanip>
#include <GL/gl.h>

#include "Vector.hpp"

Vector::Vector(float x, float y, float z):
        x(x),
        y(y),
        z(z) {
}

Vector::Vector(const Vector &a):
        x(a.x),
        y(a.y),
        z(a.z) {
}

float Vector::len() const {
    return sqrtf((*this) * (*this));
}

void Vector::glPassVertex() const {
    glVertex3f(this->x, this->y, this->z);
}

void Vector::glPassNormal() const {
    glNormal3f(this->x, this->y, this->z);
}

bool operator ==(const Vector &a, const Vector &b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool operator !=(const Vector &a, const Vector &b){
    return a.x != b.x || a.y != b.y || a.z != b.z;
}

Vector operator -(const Vector &a) {
    return Vector(a.x, a.y, a.z);
}

Vector operator +(const Vector &a, const Vector &b) {
    return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator -(const Vector &a, const Vector &b) {
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

float operator *(const Vector &a, const Vector &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector operator *(float a, const Vector &b) {
    return Vector(a * b.x, a * b.y, a * b.z);
}

Vector operator *(const Vector &b, float a) {
    return Vector(a * b.x, a * b.y, a * b.z);
}

Vector operator /(const Vector &a, float b) {
    return Vector(a.x / b, a.y / b, a.z / b);
}

Vector normalized(const Vector &a) {
    float l = a.len();
    return Vector(a.x / l, a.y / l, a.z / l);
}

Vector multiply(const Vector &a, const Vector &b) {
    return Vector(a.y * b.z - a.z * b.y, -a.x * b.z + a.z * b.x, a.x * b.y - a.y * b.x);
}

Vector normal(const Vector &a, const Vector &b) {
    return normalized(multiply(a, b));
}

float angle(const Vector &a, const Vector &b) {
    return atan2f(multiply(a, b).len(), a * b);
}

std::ostream & operator <<(std::ostream &stream, const Vector &a) {
    stream << std::setprecision(2) << "(" << a.x << ", " << a.y << ", " << a.z << ")";
    return stream;
}
