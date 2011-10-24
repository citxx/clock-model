#ifndef CLOCK_APPLICATION_HPP
#define CLOCK_APPLICATION_HPP

#include "PolygonalModel.hpp"
#include "SDL.h"

class ClockApplication {
    SDL_Surface *screen;

    int windowWidth;
    int windowHeight;
    bool isRunning;

    PolygonalModel *model;
    void drawScene();

    void processEvents();

  public:
    ClockApplication();
    ~ClockApplication();

    void mainLoop();
};

#endif  // CLOCK_APPLICATION_HPP
