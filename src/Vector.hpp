#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

class Vector {
  public:
    float x, y, z;

    Vector(float x = 0.0, float y = 0.0, float z = 0.0);
    Vector(const Vector &a);

    float len() const;

    void glPassVertex() const;
    void glPassNormal() const;

    friend std::ostream & operator <<(std::ostream &stream, const Vector &t);
};

bool operator ==(const Vector &a, const Vector &b);
bool operator !=(const Vector &a, const Vector &b);

Vector operator -(const Vector &a);
Vector operator +(const Vector &a, const Vector &b);
Vector operator -(const Vector &a, const Vector &b);
float operator *(const Vector &a, const Vector &b);

Vector operator *(float a, const Vector &b);
Vector operator *(const Vector &a, float b);
Vector operator /(const Vector &a, float b);

Vector normalized(const Vector &a);
Vector multiply(const Vector &a, const Vector &b);
float angle(const Vector &a, const Vector &b);
Vector normal(const Vector &a, const Vector &b);

std::ostream & operator <<(std::ostream &stream, const Vector &t);

#endif  // VECTOR_HPP
