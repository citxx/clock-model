#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP

#include <iostream>

class Vector3D {
  public:
    float x, y, z;

    explicit Vector3D(float x = 0.0, float y = 0.0, float z = 0.0);
    Vector3D(const Vector3D &a);

    float len() const;

    friend std::ostream & operator <<(std::ostream &stream, const Vector3D &t);
};

bool operator ==(const Vector3D &a, const Vector3D &b);
bool operator !=(const Vector3D &a, const Vector3D &b);

Vector3D operator -(const Vector3D &a);
Vector3D operator +(const Vector3D &a, const Vector3D &b);
Vector3D operator -(const Vector3D &a, const Vector3D &b);
float operator *(const Vector3D &a, const Vector3D &b);

Vector3D operator *(float a, const Vector3D &b);
Vector3D operator *(const Vector3D &a, float b);
Vector3D operator /(const Vector3D &a, float b);

Vector3D normalized(const Vector3D &a);
Vector3D crossProduct(const Vector3D &a, const Vector3D &b);
float angle(const Vector3D &a, const Vector3D &b);
Vector3D normal(const Vector3D &a, const Vector3D &b);

std::ostream & operator <<(std::ostream &stream, const Vector3D &t);

#endif  // VECTOR_3D_HPP
