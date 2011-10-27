#include <GL/gl.h>
#include <GL/glu.h>

#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(
    const GLVector &position,
    const GLVector &center,
    const GLVector &up,
    float viewField,
    float aspectRatio,
    float nearZ,
    float farZ):
        position(position),
        center(center),
        up(up),
        viewField(viewField),
        aspectRatio(aspectRatio),
        nearZ(nearZ),
        farZ(farZ) {
}

void PerspectiveCamera::glActivate() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(this->viewField, this->aspectRatio, this->nearZ, this->farZ);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(this->position.x, this->position.y, this->position.z,
              this->center.x, this->center.y, this->center.z,
              this->up.x, this->up.y, this->up.z);
}
