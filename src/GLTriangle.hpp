#ifndef GL_TRIANGLE_HPP
#define GL_TRIANGLE_HPP

#include <iostream>

#include "GLVector.hpp"

class GLTriangle {
    GLVector v1, v2, v3;

  public:
    GLTriangle(const GLVector &v1, const GLVector &v2, const GLVector &v3);
    GLTriangle(const GLTriangle &t);

    void glPass() const;

    friend std::ostream & operator <<(std::ostream &stream, const GLTriangle &t);
};

std::ostream & operator << (std::ostream &stream, const GLTriangle &t);

#endif  // GL_TRIANGLE_HPP
