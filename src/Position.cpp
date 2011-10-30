#include <cmath>
#include <GL/gl.h>

#include "Position.hpp"

Position::Position(const Vector &location, const Quaternion &rotation):
        location(location),
        rotation(rotation) {
}

Position::Position(const Vector &location, float alpha, const Vector &axis):
    location(location),
    rotation(Quaternion(cosf(alpha / 2), sinf(alpha / 2) * normalized(axis)) {
}

void Position::glActivate() {
    glTranslatef(
        this->location.x,
        this->locatoin.y,
        this->location.z
    );
    glRotatef(
        acosf(this->rotation.w),
        this->rotation.v.x,
        this->rotation.v.y,
        this->rotation.v.z
    );
}
