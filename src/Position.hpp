#ifndef POSITION_HPP
#define POSITION_HPP

#include "Rotation.hpp"
#include "Vector3D.hpp"

class Position {
    Vector3D location;
    Rotation rotation;
    Vector3D scaling;

  public:
    explicit Position(
        const Vector3D &location,
        const Rotation &rotation = Rotation(),
        const Vector3D &scaling = Vector3D(1.0, 1.0, 1.0)
    );

    void glPerform() const;
};

#endif  // POSITION_HPP
