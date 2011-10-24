#include <cmath>
#include <iomanip>
#include <GL/gl.h>

#include "GLVector.hpp"

GLVector::GLVector(float x, float y, float z, float w):
        x(x),
        y(y),
        z(z),
        w(w) {
}

GLVector::GLVector(const GLVector &a):
        x(a.x),
        y(a.y),
        z(a.z),
        w(a.w) {
}

float GLVector::len() const {
    return sqrtf((*this) * (*this));
}

void GLVector::glPassVertex() const {
    glVertex4f(this->x, this->y, this->z, this->w);
}

void GLVector::glPassNormal() const {
    glNormal3f(this->x, this->y, this->z);
}

GLVector operator -(const GLVector &a) {
    return GLVector(a.x, a.y, a.z, a.w);
}

GLVector operator +(const GLVector &a, const GLVector &b) {
    return GLVector(a.x + b.x, a.y + b.y, a.z + b.z, a.w);
}

GLVector operator -(const GLVector &a, const GLVector &b) {
    return GLVector(a.x - b.x, a.y - b.y, a.z - b.z, a.w);
}

float operator *(const GLVector &a, const GLVector &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

GLVector normalized(const GLVector &a) {
    float l = a.len();
    return GLVector(a.x / l, a.y / l, a.z / l, a.w);
}

GLVector multiply(const GLVector &a, const GLVector &b) {
    return GLVector(a.y * b.z - a.z * b.y, -a.x * b.z + a.z * b.x, a.x * b.y - a.y * b.x);
}

GLVector normal(const GLVector &a, const GLVector &b) {
    return normalized(multiply(a, b));
}

std::ostream & operator <<(std::ostream &stream, const GLVector &a) {
    stream << std::setprecision(2) << "(" << a.x << ", " << a.y << ", " << a.z << ", " << a.w << ")";
    return stream;
}
