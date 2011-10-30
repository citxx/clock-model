#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include "Vector.hpp"

class PerspectiveCamera {
    Vector location;
    Vector center;
    Vector up;
    float viewField;
    float aspectRatio;
    float nearZ;
    float farZ;

  public:
    PerspectiveCamera(
        const Vector &location,
        const Vector &center,
        const Vector &up,
        float viewField,
        float aspectRatio,
        float nearZ,
        float farZ
    );
    PerspectiveCamera(const PerspectiveCamera &cam);

    void glActivate() const;

    PerspectiveCamera rotated(float alpha, float betha) const;
    PerspectiveCamera resized(int width, int height) const;
};

#endif  // PERSPECTIVE_CAMERA_HPP
