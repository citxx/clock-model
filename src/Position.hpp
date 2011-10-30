#ifndef POSITION_HPP
#define POSITION_HPP

#include "Quaternion.hpp"
#include "Vector.hpp"

class Position {
    Vector location;
    Quaternion rotation;

  public:
    Position(const Vector &location, const Quaternion &rotation);
    Position(const Vector &location, float alpha, const Vector &axis);
    explicit Position(const Vector &location);

    void glActivate() const;
};

#endif  // POSITION_HPP
