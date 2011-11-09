#include <cmath>
#include <iostream>
#include <GL/gl.h>

#include "Position.hpp"

Position::Position(
    const Vector3D &location,
    const Rotation &rotation,
    const Vector3D &scaling
):
        location(location),
        rotation(rotation),
        scaling(scaling) {
}

void Position::glPerform() const {
    glTranslatef(
        this->location.x,
        this->location.y,
        this->location.z
    );
    this->rotation.glPerform();
    glScalef(
        this->scaling.x,
        this->scaling.y,
        this->scaling.z
    );
}
