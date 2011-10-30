#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include "GLVector.hpp"

class PerspectiveCamera {
    GLVector location;
    GLVector center;
    GLVector up;
    float viewField;
    float aspectRatio;
    float nearZ;
    float farZ;

  public:
    PerspectiveCamera(
        const GLVector &location,
        const GLVector &center,
        const GLVector &up,
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
