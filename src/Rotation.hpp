#ifndef ROTATION_HPP
#define ROTATION_HPP

#include "Quaternion.hpp"
#include "Vector3D.hpp"

class Rotation {
    Quaternion r;

  public:
    Rotation();
    Rotation(const Quaternion &q);
    Rotation(float angle, const Vector3D &axis);
    Rotation(float angle, float x, float y, float z);

    void glPerform() const;

    friend Rotation operator *(const Rotation &a, const Rotation &b);
};

Rotation operator *(const Rotation &a, const Rotation &b);

#endif  // ROTATION_HPP
