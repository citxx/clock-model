#ifndef POLYGONAL_MODEL_HPP
#define POLYGONAL_MODEL_HPP

#include <GL/gl.h>
#include <string>
#include <vector>

#include "Position.hpp"
#include "Vector.hpp"

class PolygonalModel {
    GLuint listNum;

  public:
    PolygonalModel(std::string fileName);
    ~PolygonalModel();

    void glDraw(const Position &position) const;
};


#endif  // POLYGONAL_MODEL_HPP
