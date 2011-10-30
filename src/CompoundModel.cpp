#include <GL/gl.h>

#include "CompoundModel.hpp"

CompoundModel::CompoundModel(
    std::vector <Model *> models,
    std::vector <Position> positions
):
        models(models),
        positions(positions) {
    if (models.size() != positions.size()) {
        throw "CompoundModel: error: sizes of 'models' and 'positions' are not equal";
    }
}

void CompoundModel::glDraw(const Position &position) const {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        position.glPerform();
        for (int i = 0; i < (int)models.size(); i++) {
            this->models[i]->glDraw(this->positions[i]);
        }
    glPopMatrix();
}
