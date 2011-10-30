#ifndef POSITION_HPP
#define POSITION_HPP

#include "Rotation.hpp"
#include "Vector.hpp"

class Position {
    Vector location;
    Rotation rotation;
    Vector scaling;

  public:
    explicit Position(
        const Vector &location,
        const Rotation &rotation = Rotation(),
        const Vector &scaling = Vector(1.0, 1.0, 1.0)
    );

    void glPerform() const;
};

#endif  // POSITION_HPP
