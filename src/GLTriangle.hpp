#ifndef GL_TRIANGLE_HPP
#define GL_TRIANGLE_HPP

#include <iostream>

#include "Vector.hpp"

class GLTriangle {
    Vector v1, v2, v3;

  public:
    GLTriangle(const Vector &v1, const Vector &v2, const Vector &v3);
    GLTriangle(const GLTriangle &t);

    void glPass() const;

    friend std::ostream & operator <<(std::ostream &stream, const GLTriangle &t);
};

std::ostream & operator << (std::ostream &stream, const GLTriangle &t);

#endif  // GL_TRIANGLE_HPP
