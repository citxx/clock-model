#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include "GLVector.hpp"

class PerspectiveCamera {
    GLVector position;
    GLVector center;
    GLVector up;
    float viewField;
    float aspectRatio;
    float nearZ;
    float farZ;

  public:
    PerspectiveCamera(
        const GLVector &position,
        const GLVector &center,
        const GLVector &up,
        float viewField,
        float aspectRatio,
        float nearZ,
        float farZ
    );

    void glActivate();
};

#endif  // PERSPECTIVE_CAMERA_HPP
