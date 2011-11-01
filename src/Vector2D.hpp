#ifndef VECTOR_2D_HPP
#define VECTOR_2D_HPP

#include <iostream>

class Vector2D {
  public:
    float x, y;

    explicit Vector2D(float x = 0.0, float y = 0.0);
    Vector2D(const Vector2D &a);

    float len() const;

    friend std::ostream & operator <<(std::ostream &stream, const Vector2D &t);
};

bool operator ==(const Vector2D &a, const Vector2D &b);
bool operator !=(const Vector2D &a, const Vector2D &b);

Vector2D operator -(const Vector2D &a);
Vector2D operator +(const Vector2D &a, const Vector2D &b);
Vector2D operator -(const Vector2D &a, const Vector2D &b);
float operator *(const Vector2D &a, const Vector2D &b);

Vector2D operator *(float a, const Vector2D &b);
Vector2D operator *(const Vector2D &a, float b);
Vector2D operator /(const Vector2D &a, float b);

Vector2D normalized(const Vector2D &a);
float crossProduct(const Vector2D &a, const Vector2D &b);
float angle(const Vector2D &a, const Vector2D &b);
Vector2D normal(const Vector2D &a);

std::ostream & operator <<(std::ostream &stream, const Vector2D &t);

#endif  // VECTOR_2D_HPP
