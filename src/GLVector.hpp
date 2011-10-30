#ifndef GL_VECTOR_HPP
#define GL_VECTOR_HPP

#include <iostream>

class GLVector {
  public:
    float x, y, z;

    GLVector(float x = 0.0, float y = 0.0, float z = 0.0);
    GLVector(const GLVector &a);

    float len() const;

    void glPassVertex() const;
    void glPassNormal() const;

    friend std::ostream & operator <<(std::ostream &stream, const GLVector &t);
};

bool operator ==(const GLVector &a, const GLVector &b);
bool operator !=(const GLVector &a, const GLVector &b);

GLVector operator -(const GLVector &a);
GLVector operator +(const GLVector &a, const GLVector &b);
GLVector operator -(const GLVector &a, const GLVector &b);
float operator *(const GLVector &a, const GLVector &b);
GLVector operator *(float a, const GLVector &b);
GLVector operator *(GLVector &b, float a);
GLVector normalized(const GLVector &a);
GLVector multiply(const GLVector &a, const GLVector &b);
float angle(const GLVector &a, const GLVector &b);
GLVector normal(const GLVector &a, const GLVector &b);

std::ostream & operator <<(std::ostream &stream, const GLVector &t);

#endif  // GL_VECTOR_HPP
