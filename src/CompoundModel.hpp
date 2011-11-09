#ifndef COMPOUND_MODEL_HPP
#define COMPOUND_MODEL_HPP

#include <vector>

#include "Model.hpp"

class CompoundModel: public Model {
    std::vector <Model *> models;
    std::vector <Position> positions;

  public:
    CompoundModel(
        std::vector <Model *> models,
        std::vector <Position> positions
    );

    virtual void glDraw(const Position &position) const;
};

#endif  // COMPOUND_MODEL_HPP
