#ifndef POLYGONAL_MODEL_HPP
#define POLYGONAL_MODEL_HPP

#include <GL/gl.h>
#include <string>
#include <vector>

#include "Vector.hpp"

class PolygonalModel {
    GLuint listNum;

  public:
    PolygonalModel(std::string fileName);
    ~PolygonalModel();

    void glDraw(
        const Vector &position,
        const Vector &direction = Vector(1.0, 0.0, 0.0),
        float angle = 0.0
    ) const;
};


#endif  // POLYGONAL_MODEL_HPP
