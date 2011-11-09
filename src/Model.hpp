#ifndef MODEL_HPP
#define MODEL_HPP

#include "Position.hpp"

class Model {
  public:
    virtual ~Model() {};
    virtual void glDraw(const Position &position) const = 0;
};

#endif  // MODEL_HPP
