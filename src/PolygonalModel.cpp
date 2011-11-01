#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <cmath>

#include "Vector3D.hpp"
#include "GLVertex.hpp"
#include "GLFace.hpp"
#include "PolygonalModel.hpp"

PolygonalModel::PolygonalModel(std::string fileName) {
    std::cerr << "Loading model from file '" << fileName << "'... ";

    this->listNum = glGenLists(1);

    if (fileName.rfind(".obj") + 4 != fileName.length()) {
        throw "PolygonalModel: error: invalid file name";
    }

    std::fstream modelStream(fileName.c_str(), std::ios_base::in);
    if (!modelStream.is_open()) {
        throw "PolygonalModel: error: cannot open file";
    }

    std::string line;
    std::vector <Vector3D> vertices;
    std::vector <Vector3D> normals;
    std::vector <GLFace> faces;
    while (std::getline(modelStream, line)) {
        if (line.find("v ") == 0) {
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
        else if (line.find("f ") == 0) {
            std::stringstream stream(line.substr(2));
            std::vector <std::string> tokens;
            std::copy(
                std::istream_iterator <std::string>(stream),
                std::istream_iterator <std::string>(),
                std::back_inserter <std::vector <std::string> >(tokens)
            );
            std::vector <GLVertex> vFace;
            for (std::vector <std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
                std::replace(it->begin(), it->end(), '/', ' ');
                std::stringstream elementStream(*it);
                int vi, vni;
                elementStream >> vi >> vni;
                vFace.push_back(GLVertex(vertices[vi - 1], normals[vni - 1]));
            }
            for (int i = 2; i < (int)vFace.size(); i++) {
                faces.push_back(GLFace(vFace[0], vFace[i - 1], vFace[i]));
            }
        }
        else if (line.find("#") == 0) {
            // Just a comment. Do nothing.
        }
        else {
            // Unsupported command. Do nothing.
        }
    }
    std::cerr << "done." << std::endl;

    std::cerr << "Creating display list number " << this->listNum << " for '" << fileName << "'... ";
    glNewList(this->listNum, GL_COMPILE);
        glBegin(GL_TRIANGLES);
            for (std::vector <GLFace>::iterator f = faces.begin(); f != faces.end(); ++f) {
                f->glPass();
            }
        glEnd();
    glEndList();
    std::cerr << "done." << std::endl;
}

PolygonalModel::~PolygonalModel() {
    std::cerr << "Deleting display list number " << this->listNum << "... ";
    glDeleteLists(this->listNum, 1);
    std::cerr << "done." << std::endl;
}

void PolygonalModel::glDraw(const Position &position) const {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        position.glPerform();
        glCallList(this->listNum);
    glPopMatrix();
}
