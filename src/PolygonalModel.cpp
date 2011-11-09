#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <cmath>

#include "GLVertex.hpp"
#include "PolygonalModel.hpp"
#include "Vector3D.hpp"
#include "Vector2D.hpp"

PolygonalModel::PolygonalModel(std::string fileName) {
    std::cerr << "Loading model from file '" << fileName << "'... ";

    if (fileName.rfind(".obj") + 4 != fileName.length()) {
        throw "PolygonalModel: error: invalid file name";
    }

    std::fstream modelStream(fileName.c_str(), std::ios_base::in);
    if (!modelStream.is_open()) {
        throw "PolygonalModel: error: cannot open file";
    }

    std::string line;
    std::vector <Vector3D> vertices;
    std::vector <Vector2D> uvs;
    std::vector <Vector3D> normals;
    std::vector <Vector3D> faceVs;
    std::vector <Vector2D> faceUvs;
    std::vector <Vector3D> faceNs;

    while (std::getline(modelStream, line)) {
        if (line.find("mtllib ") == 0) {
            std::stringstream stream(line.substr(7));
            std::string fileName;
            stream >> fileName;
            this->materials = Material::readMTL(fileName);
        }
        else if (line.find("usemtl ") == 0) {
            std::stringstream stream(line.substr(7));
            std::string materialName;
            stream >> materialName;
            this->groups.push_back(materialName);
            this->groupStarts.push_back(faceVs.size());
        }
        else if (line.find("v ") == 0) {
            std::stringstream stream(line.substr(2));
            float x, y, z;
            stream >> x >> y >> z;
            vertices.push_back(Vector3D(x, y, z));
        }
        else if (line.find("vn ") == 0) {
            std::stringstream stream(line.substr(3));
            float x, y, z;
            stream >> x >> y >> z;
            normals.push_back(Vector3D(x, y, z));
        }
        else if (line.find("vt ") == 0) {
            std::stringstream stream(line.substr(3));
            float u, v;
            stream >> u >> v;
            uvs.push_back(Vector2D(u, v));
        }
        else if (line.find("f ") == 0) {
            std::stringstream stream(line.substr(2));
            std::vector <std::string> tokens;
            std::copy(
                std::istream_iterator <std::string>(stream),
                std::istream_iterator <std::string>(),
                std::back_inserter <std::vector <std::string> >(tokens)
            );
            for (std::vector <std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
                std::replace(it->begin(), it->end(), '/', ' ');
                std::stringstream elementStream(*it);
                int vi, vti, vni;
                elementStream >> vi >> vti >> vni;
                faceVs.push_back(vertices[vi - 1]);
                faceUvs.push_back(uvs[vti - 1]);
                faceNs.push_back(normals[vni - 1]);
            }
        }
        else if (line.find("#") == 0) {
            // Just a comment. Do nothing.
        }
        else {
            // Unsupported command. Do nothing.
        }
    }

    this->groupStarts.push_back(faceVs.size());

    this->vertices = new float[3 * faceVs.size()];
    for (int i = 0; i < (int)faceVs.size(); i++) {
        this->vertices[3 * i] = faceVs[i].x;
        this->vertices[3 * i + 1] = faceVs[i].y;
        this->vertices[3 * i + 2] = faceVs[i].z;
    }

    this->uvs = new float[2 * faceUvs.size()];
    for (int i = 0; i < (int)faceUvs.size(); i++) {
        this->uvs[2 * i] = faceUvs[i].x;
        this->uvs[2 * i + 1] = faceUvs[i].y;
    }

    this->normals = new float[3 * faceNs.size()];
    for (int i = 0; i < (int)faceNs.size(); i++) {
        this->normals[3 * i] = faceNs[i].x;
        this->normals[3 * i + 1] = faceNs[i].y;
        this->normals[3 * i + 2] = faceNs[i].z;
    }

    std::cerr << "done." << std::endl;
}

PolygonalModel::~PolygonalModel() {
    delete []this->vertices;
    delete []this->uvs;
    delete []this->normals;
}

void PolygonalModel::glDraw(const Position &position) const {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        position.glPerform();
        glEnable(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, this->vertices);
        glEnable(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, this->uvs);
        glEnable(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, this->normals);
        for (int groupNum = 0; groupNum < (int)this->groups.size(); groupNum++) {
            this->materials.find(this->groups[groupNum])->second.glActivate();
            glDrawArrays(
                GL_TRIANGLES,
                this->groupStarts[groupNum],
                this->groupStarts[groupNum + 1] - this->groupStarts[groupNum]
            );
        }
    glPopMatrix();
}
