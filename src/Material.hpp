#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <GL/gl.h>
#include <map>
#include <string>

#include "Color.hpp"

class Material {
    GLuint textureNum;
    Color ambient;
    Color diffuse;
    Color specular;
    float shininess;
    Color emission;

  public:
    Material();
    Material(
        const Color &ambient,
        const Color &diffuse,
        const Color &specular,
        float shininess = 0.0,
        const Color &emission = Color(0.0)
    );
    Material(
        std::string textureFileName,
        const Color &ambient,
        const Color &diffuse,
        const Color &specular,
        float shininess = 0.0,
        const Color &emission = Color(0.0)
    );
    Material(const Material &m);

    Material & operator =(const Material &m);

    static std::map <std::string, Material> readMTL(std::string fileName);

    void glActivate() const;
};

#endif  // MATERIAL_HPP
