#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include "Vector3D.hpp"

class PerspectiveCamera {
    Vector3D location;
    Vector3D center;
    Vector3D up;
    float viewField;
    float aspectRatio;
    float nearZ;
    float farZ;

  public:
    PerspectiveCamera(
        const Vector3D &location,
        const Vector3D &center,
        const Vector3D &up,
        float viewField,
        float aspectRatio,
        float nearZ,
        float farZ
    );
    PerspectiveCamera(const PerspectiveCamera &cam);

    void glActivate() const;

    PerspectiveCamera rotated(float alpha, float betha) const;
    PerspectiveCamera resized(int width, int height) const;
    PerspectiveCamera moved(const Vector3D &v) const;
    PerspectiveCamera redistanted(float diffDistance) const;
};

#endif  // PERSPECTIVE_CAMERA_HPP
