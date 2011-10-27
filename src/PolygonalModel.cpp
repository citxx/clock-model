#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#include "GLVector.hpp"
#include "GLTriangle.hpp"
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
    std::vector <GLVector> vertices;
    std::vector <GLTriangle> faces;
    while (std::getline(modelStream, line)) {
//        std::cerr << "Line: " << line << std::endl;
        if (line.find("v ") == 0) {
            std::stringstream stream(line.substr(2));
            float x, y, z;
            stream >> x >> y >> z;
            vertices.push_back(GLVector(x, y, z));
        }
        else if (line.find("f ") == 0) {
            std::stringstream stream(line.substr(2));
            int start, i, j;
            stream >> start >> j;
            start -= 1;
            j -= 1;
            while (stream >> i) {
                i -= 1;
                std::swap(i, j);
                faces.push_back(GLTriangle(vertices[start], vertices[i], vertices[j]));
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
            for (std::vector <GLTriangle>::iterator f = faces.begin(); f != faces.end(); ++f) {
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

void PolygonalModel::glDraw(
    const GLVector &position,
    const GLVector &direction,
    float selfAngle
) const {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        GLVector rotationAxis = multiply(GLVector(1.0, 0.0, 0.0), direction);
        float rotationAngle = angle(GLVector(1.0, 0.0, 0.0), direction);
//        std::cerr << "Rotation: " << rotationAxis << " " << rotationAngle / M_PI * 180.0 << std::endl;
        glRotatef(rotationAngle / M_PI * 180.0, rotationAxis.x, rotationAxis.y, rotationAxis.z);
        glRotatef(selfAngle, 1.0, 0.0, 0.0);
        glCallList(this->listNum);
    glPopMatrix();
}
