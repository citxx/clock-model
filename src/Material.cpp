#include <iostream>
#include <fstream>
#include <GL/glu.h>
#include "SDL_image.h"
#include <sstream>

#include "Material.hpp"

Material::Material():
        textureNum(0),
        ambient(0.2),
        diffuse(0.8),
        specular(0.0),
        shininess(0.0),
        emission(0.0) {
}

Material::Material(
    std::string textureFileName,
    const Color &ambient,
    const Color &diffuse,
    const Color &specular,
    float shininess,
    const Color &emission
):
        textureNum(0),
        ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        shininess(shinines / 128.0),
        emission(emission) {
    SDL_Surface *img;
    void *raw;
    int w, h, bpp;
    Uint8 *srcPixel, *dstPixel;
    Uint32 truePixel;
    GLenum errorCode;

    img = IMG_Load(textureFileName.c_str());

    if (!img) {
        throw "SDL_Image load error";
    }
    if (img->format->BytesPerPixel < 2) {
        throw "Bad image - not true color!";
    }

    raw = (void *)malloc(img->w * img->h * 4);
    dstPixel = (Uint8 *)raw;

    SDL_LockSurface(img);
    bpp = img->format->BytesPerPixel;

    for (int i = img->h; i > 0; i--) {
        for (int j = 0; j < img->w; j++) {
            srcPixel = (Uint8 *)img->pixels + i * img->pitch + j * bpp;
            switch (bpp) {
                case 1:
                    truePixel = *srcPixel;
                    break;

                case 2:
                    truePixel = *(Uint16 *)srcPixel;
                    break;

                case 3:
                    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                        truePixel = srcPixel[0] << 16 | srcPixel[1] << 8 | srcPixel[2];
                    } else {
                        truePixel = srcPixel[0] | srcPixel[1] << 8 | srcPixel[2] << 16;
                    }
                    break;

                case 4:
                    truePixel = *(Uint32 *)srcPixel;
                    break;

                default:
                    throw "Image bpp is unsupported\n";
                    break;
            }
            SDL_GetRGBA(truePixel, img->format, &(dstPixel[0]), &(dstPixel[1]), &(dstPixel[2]), &(dstPixel[3]));
            dstPixel += 4;
        }
    }

    w = img->w;
    h = img->h;

    SDL_UnlockSurface(img);
    SDL_FreeSurface(img);

    glGenTextures(1, &this->textureNum);
    glBindTexture(GL_TEXTURE_2D, this->textureNum);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    errorCode = glGetError();
    if (errorCode != 0) {
        if (errorCode == GL_OUT_OF_MEMORY) {
            throw "Out of texture memory!";
        }
        else {
            throw "Unknown OpenGL error";
        }
    }

    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_RGBA, GL_UNSIGNED_BYTE, (Uint8 *)raw);

    errorCode = glGetError();
    if (errorCode != 0) {
        if (errorCode == GL_OUT_OF_MEMORY) {
            throw "Out of texture memory!";
        }
        else {
            throw "Unknown OpenGL error";
        }
    }
}

Material::Material(
    const Color &ambient,
    const Color &diffuse,
    const Color &specular,
    float shininess,
    const Color &emission
):
        textureNum(0),
        ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        shininess(shininess / 128.0),
        emission(emission) {
}

Material::Material(const Material &m):
        textureNum(m.textureNum),
        ambient(m.ambient),
        diffuse(m.diffuse),
        specular(m.specular),
        shininess(m.shininess),
        emission(m.emission) {
}

Material & Material::operator =(const Material &m) {
    this->textureNum = m.textureNum;
    this->ambient = m.ambient;
    this->diffuse = m.diffuse;
    this->specular = m.specular;
    this->shininess = m.shininess;
    this->emission = m.emission;
    return *this;
}

void Material::glActivate() const {
    glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient.getData());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse.getData());
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->specular.getData());
    glMaterialf(GL_FRONT, GL_SHININESS, this->shininess * 128);
    glMaterialfv(GL_FRONT, GL_EMISSION, this->emission.getData());

    if (this->textureNum == 0) {
        glDisable(GL_TEXTURE_2D);
    }
    else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->textureNum);
    }
}

std::map <std::string, Material> Material::readMTL(std::string fileName) {
    std::map <std::string, Material> result;

    std::string name = "";
    std::string textureName = "";
    Color ambient;
    Color diffuse;
    Color specular;
    float shininess = 0.0;
    Color emission;

    std::fstream fileStream(fileName.c_str(), std::ios_base::in);
    std::string line;
    while (getline(fileStream, line)) {
        if (line.find("newmtl ") == 0) {
            if (name != "") {
                if (textureName != "") {
                    result[name] = Material(
                        textureName,
                        ambient,
                        diffuse,
                        specular,
                        shininess,
                        emission
                    );
                }
                else {
                    result[name] = Material(
                        ambient,
                        diffuse,
                        specular,
                        shininess,
                        emission
                    );
                }
            }
            std::stringstream s(line.substr(7));
            s >> name;
            textureName = "";
            ambient = Color(0.2);
            diffuse = Color(0.8);
            specular = Color(0.0);
            emission = Color(0.0);
            shininess = 0.0;
        }
        else if (line.find("Ns ") == 0) {
            std::stringstream s(line.substr(3));
            float ns;
            s >> ns;
            shininess = ns / 1000.0 * 128.0;
        }
        else if (line.find("Ka ") == 0) {
            std::stringstream s(line.substr(3));
            float r, g, b;
            s >> r >> g >> b;
            ambient = Color(r, g, b);
        }
        else if (line.find("Kd ") == 0) {
            std::stringstream s(line.substr(3));
            float r, g, b;
            s >> r >> g >> b;
            diffuse = Color(r, g, b);
        }
        else if (line.find("Ks ") == 0) {
            std::stringstream s(line.substr(3));
            float r, g, b;
            s >> r >> g >> b;
            specular = Color(r, g, b);
        }
        else if (line.find("map_Kd ") == 0) {
            std::stringstream s(line.substr(7));
            s >> textureName;
        }
        else if (line.find("#") == 0) {
            // Comment. Do nothing.
        }
        else {
            // Unknown command. Do nothing.
        }
    }
    if (name != "") {
        if (textureName != "") {
            result[name] = Material(
                textureName,
                ambient,
                diffuse,
                specular,
                shininess,
                emission
            );
        }
        else {
            result[name] = Material(
                ambient,
                diffuse,
                specular,
                shininess,
                emission
            );
        }
    }

    return result;
}
