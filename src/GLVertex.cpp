#include <GL/gl.h>

#include "GLVertex.hpp"

GLVertex::GLVertex(const Vector3D &location, const Vector3D &normal):
        location(location),
        normal(normal) {
}

void GLVertex::glPass() const {
    glNormal3f(
        this->normal.x,
        this->normal.y,
        this->normal.z
    );
    glVertex3f(
        this->location.x,
        this->location.y,
        this->location.z
    );
}
