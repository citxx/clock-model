#ifndef GL_TRIANGLE_HPP
#define GL_TRIANGLE_HPP

#include <iostream>

#include "GLVertex.hpp"

class GLFace {
    GLVertex v1, v2, v3;

  public:
    GLFace(const GLVertex &v1, const GLVertex &v2, const GLVertex &v3);
    GLFace(const GLFace &t);

    void glPass() const;

    friend std::ostream & operator <<(std::ostream &stream, const GLFace &t);
};

std::ostream & operator << (std::ostream &stream, const GLFace &t);

#endif  // GL_TRIANGLE_HPP
