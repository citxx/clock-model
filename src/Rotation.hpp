#ifndef ROTATION_HPP
#define ROTATION_HPP

#include "Quaternion.hpp"
#include "Vector.hpp"

class Rotation {
    Quaternion r;

  public:
    Rotation(const Quaternion &q);
    Rotation(float angle, const Vector &axis);
    Rotation(float angle, float x, float y, float z);

    void glPerform() const;

    friend Rotation operator *(const Rotation &a, const Rotation &b);
};

Rotation operator *(const Rotation &a, const Rotation &b);

#endif  // ROTATION_HPP
