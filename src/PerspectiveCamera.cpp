#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(
    const Vector3D &location,
    const Vector3D &center,
    const Vector3D &up,
    float viewField,
    float aspectRatio,
    float nearZ,
    float farZ):
        location(location),
        center(center),
        up(up),
        viewField(viewField),
        aspectRatio(aspectRatio),
        nearZ(nearZ),
        farZ(farZ) {
    Vector3D direction = this->location - this->center;
    this->up = normalized(this->up - (this->up * normalized(direction)) * normalized(direction));
    if (this->up.len() < 1e-5) {
        throw "PerspectiveCamera: error: invalid value of up vector";
    }
}

PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera &cam):
        location(cam.location),
        center(cam.center),
        up(cam.up),
        viewField(cam.viewField),
        aspectRatio(cam.aspectRatio),
        nearZ(cam.nearZ),
        farZ(cam.farZ) {
}

void PerspectiveCamera::glActivate() const {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(this->viewField, this->aspectRatio, this->nearZ, this->farZ);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(this->location.x, this->location.y, this->location.z,
              this->center.x, this->center.y, this->center.z,
              this->up.x, this->up.y, this->up.z);
}

PerspectiveCamera PerspectiveCamera::rotated(float alpha, float betha) const {
    float alphaR = alpha * M_PI / 180.0;
    float bethaR = -betha * M_PI / 180.0;
//    std::cerr << alphaR << " " << bethaR << std::endl;
    Vector3D direction = this->location - this->center;
    Vector3D left = normalized(normal(direction, this->up));

    Vector3D add = (tanf(bethaR) * direction.len()) * this->up +
                   (tanf(alphaR) * direction.len()) * left;

    Vector3D newDirection = direction.len() * normalized(direction + add);

//    std::cerr << newDirection << this->up << std::endl;
    return PerspectiveCamera(
        this->center + newDirection,
        this->center,
        this->up,
        this->viewField,
        this->aspectRatio,
        this->nearZ,
        this->farZ
    );
}

PerspectiveCamera PerspectiveCamera::resized(int width, int height) const {
    return PerspectiveCamera(
        this->location,
        this->center,
        this->up,
        this->viewField,
        (float)width / height,
        this->nearZ,
        this->farZ
    );
}
