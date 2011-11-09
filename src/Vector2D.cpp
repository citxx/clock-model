#include <cmath>
#include <iomanip>

#include "Vector2D.hpp"

Vector2D::Vector2D(float x, float y):
        x(x),
        y(y) {
}

Vector2D::Vector2D(const Vector2D &a):
        x(a.x),
        y(a.y) {
}

float Vector2D::len() const {
    return sqrtf((*this) * (*this));
}

bool operator ==(const Vector2D &a, const Vector2D &b) {
    return a.x == b.x && a.y == b.y;
}

bool operator !=(const Vector2D &a, const Vector2D &b){
    return a.x != b.x || a.y != b.y;
}

Vector2D operator -(const Vector2D &a) {
    return Vector2D(a.x, a.y);
}

Vector2D operator +(const Vector2D &a, const Vector2D &b) {
    return Vector2D(a.x + b.x, a.y + b.y);
}

Vector2D operator -(const Vector2D &a, const Vector2D &b) {
    return Vector2D(a.x - b.x, a.y - b.y);
}

float operator *(const Vector2D &a, const Vector2D &b) {
    return a.x * b.x + a.y * b.y;
}

Vector2D operator *(float a, const Vector2D &b) {
    return Vector2D(a * b.x, a * b.y);
}

Vector2D operator *(const Vector2D &b, float a) {
    return Vector2D(a * b.x, a * b.y);
}

Vector2D operator /(const Vector2D &a, float b) {
    return Vector2D(a.x / b, a.y / b);
}

Vector2D normalized(const Vector2D &a) {
    return a / a.len();
}

float crossProduct(const Vector2D &a, const Vector2D &b) {
    return a.x * b.y - a.y * b.x;
}

Vector2D normal(const Vector2D &a) {
    return Vector2D(a.y, -a.x);
}

float angle(const Vector2D &a, const Vector2D &b) {
    return atan2f(crossProduct(a, b), a * b);
}

std::ostream & operator <<(std::ostream &stream, const Vector2D &a) {
    stream << std::setprecision(2) << "(" << a.x << ", " << a.y << ")";
    return stream;
}
