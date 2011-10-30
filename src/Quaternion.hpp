#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Vector.hpp"

class Quaternion {
  public:
    Quaternion(float w, const Vector &v);
    Quaternion(float w, float x, float y, float z);

    float w;
    Vector v;
};

bool operator ==(const Quaternion &a, const Quaternion &b);
bool operator !=(const Quaternion &a, const Quaternion &b);

Quaternion operator -(const Quaternion &a);
Quaternion operator +(const Quaternion &a, const Quaternion &b);
Quaternion operator -(const Quaternion &a, const Quaternion &b);
Quaternion operator *(const Quaternion &a, const Quaternion &b);

Quaternion operator *(float a, const Quaternion &b);
Quaternion operator *(Quaternion &b, float a);

std::ostream & operator <<(std::ostream &stream, const Quaternion &t);

#endif  // QUATERNION_HPP
