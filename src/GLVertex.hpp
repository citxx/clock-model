#ifndef GL_VERTEX_HPP
#define GL_VERTEX_HPP

#include "Vector2D.hpp"
#include "Vector3D.hpp"

class GLVertex {
    Vector3D location;
    Vector3D normal;
    Vector2D uv;

  public:
    GLVertex(const Vector3D &location, const Vector3D &normal);

    void glPass() const;
};

#endif  // GL_VERTEX_HPP
