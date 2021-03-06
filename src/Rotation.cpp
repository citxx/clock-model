#include <cmath>
#include <GL/gl.h>

#include "Rotation.hpp"

Rotation::Rotation():
        r(1.0, Vector3D(0.0, 0.0, 0.0)) {
}

Rotation::Rotation(const Quaternion &q):
        r(q) {
}

Rotation::Rotation(float angle, const Vector3D &axis):
        r(cosf(angle / 2), sinf(angle / 2) * normalized(axis)) {
}

Rotation::Rotation(float angle, float x, float y, float z):
        r(cosf(angle / 2), sinf(angle / 2) * normalized(Vector3D(x, y, z))) {
}

void Rotation::glPerform() const {
    glRotatef(
        acosf(this->r.w) * 360.0 / M_PI,
        this->r.v.x,
        this->r.v.y,
        this->r.v.z
    );
}

Rotation operator *(const Rotation &a, const Rotation &b) {
    return Rotation(a.r * b.r);
}
