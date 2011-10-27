#include <cmath>
#include <iomanip>
#include <GL/gl.h>

#include "GLVector.hpp"

GLVector::GLVector(float x, float y, float z):
        x(x),
        y(y),
        z(z) {
}

GLVector::GLVector(const GLVector &a):
        x(a.x),
        y(a.y),
        z(a.z) {
}

float GLVector::len() const {
    return sqrtf((*this) * (*this));
}

void GLVector::glPassVertex() const {
    glVertex3f(this->x, this->y, this->z);
}

void GLVector::glPassNormal() const {
    glNormal3f(this->x, this->y, this->z);
}

GLVector operator -(const GLVector &a) {
    return GLVector(a.x, a.y, a.z);
}

GLVector operator +(const GLVector &a, const GLVector &b) {
    return GLVector(a.x + b.x, a.y + b.y, a.z + b.z);
}

GLVector operator -(const GLVector &a, const GLVector &b) {
    return GLVector(a.x - b.x, a.y - b.y, a.z - b.z);
}

float operator *(const GLVector &a, const GLVector &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

GLVector normalized(const GLVector &a) {
    float l = a.len();
    return GLVector(a.x / l, a.y / l, a.z / l);
}

GLVector multiply(const GLVector &a, const GLVector &b) {
    return GLVector(a.y * b.z - a.z * b.y, -a.x * b.z + a.z * b.x, a.x * b.y - a.y * b.x);
}

GLVector normal(const GLVector &a, const GLVector &b) {
    return normalized(multiply(a, b));
}

float angle(const GLVector &a, const GLVector &b) {
    return atan2f(multiply(a, b).len(), a * b);
}

std::ostream & operator <<(std::ostream &stream, const GLVector &a) {
    stream << std::setprecision(2) << "(" << a.x << ", " << a.y << ", " << a.z << ")";
    return stream;
}
