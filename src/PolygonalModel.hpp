#ifndef POLYGONAL_MODEL_HPP
#define POLYGONAL_MODEL_HPP

#include <GL/gl.h>
#include <string>
#include <map>
#include <vector>

#include "Material.hpp"
#include "Model.hpp"
#include "Position.hpp"
#include "Vector3D.hpp"

class PolygonalModel: public Model {
    std::map <std::string, Material> materials;
    std::vector <std::string> groups;
    float *vertices;
    float *uvs;
    float *normals;
    std::vector <int> groupStarts;

  public:
    PolygonalModel(std::string fileName);
    ~PolygonalModel();

    virtual void glDraw(const Position &position) const;
};


#endif  // POLYGONAL_MODEL_HPP
