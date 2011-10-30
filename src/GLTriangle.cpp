#include "GLTriangle.hpp"

GLTriangle::GLTriangle(const Vector &v1, const Vector &v2, const Vector &v3):
        v1(v1),
        v2(v2),
        v3(v3) {
}

GLTriangle::GLTriangle(const GLTriangle &t):
        v1(t.v1),
        v2(t.v2),
        v3(t.v3) {
}

void GLTriangle::glPass() const {
    normal(v2 - v1, v3 - v1).glPassNormal();
    this->v1.glPassVertex();
    this->v2.glPassVertex();
    this->v3.glPassVertex();
}

std::ostream & operator << (std::ostream &stream, const GLTriangle &t) {
    stream << "(Triangle " << t.v1 << " " << t.v2 << " " << t.v3 << ")";
    return stream;
}
