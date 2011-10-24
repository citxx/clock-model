#ifndef POLYGONAL_MODEL_HPP
#define POLYGONAL_MODEL_HPP

#include <string>
#include <vector>
#include <GL/gl.h>

class PolygonalModel {
    GLuint listNum;

  public:
    PolygonalModel(std::string fileName);
    ~PolygonalModel();

    void glDraw() const;
};


#endif  // POLYGONAL_MODEL_HPP
