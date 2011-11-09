#include <GL/gl.h>

#include "GLVertex.hpp"

GLVertex::GLVertex(const Vector3D &location, const Vector2D &uv, const Vector3D &normal):
        location(location),
        uv(uv),
        normal(normal) {
}

void GLVertex::glPass() const {
    glNormal3f(
        this->normal.x,
        this->normal.y,
        this->normal.z
    );
    glTexCoord2f(
        this->uv.x,
        this->uv.y
    );
    glVertex3f(
        this->location.x,
        this->location.y,
        this->location.z
    );
}
