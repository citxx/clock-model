#include "GLFace.hpp"

GLFace::GLFace(const GLVertex &v1, const GLVertex &v2, const GLVertex &v3):
        v1(v1),
        v2(v2),
        v3(v3) {
}

GLFace::GLFace(const GLFace &t):
        v1(t.v1),
        v2(t.v2),
        v3(t.v3) {
}

void GLFace::glPass() const {
    this->v1.glPass();
    this->v2.glPass();
    this->v3.glPass();
}

std::ostream & operator << (std::ostream &stream, const GLFace &t) {
//    stream << "(Face " << t.v1 << " " << t.v2 << " " << t.v3 << ")"; // TODO: implement
    return stream;
}
