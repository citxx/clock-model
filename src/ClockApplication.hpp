#ifndef CLOCK_APPLICATION_HPP
#define CLOCK_APPLICATION_HPP

#include "Vector.hpp"
#include "PerspectiveCamera.hpp"
#include "PolygonalModel.hpp"
#include "SDL.h"

class ClockApplication {
    SDL_Surface *screen;

    int windowWidth;
    int windowHeight;
    bool isRunning;

    PerspectiveCamera mainCamera;

    bool isRotating;
    Vector rotateStart;
    Vector rotateEnd;
    PerspectiveCamera cameraStart;

    PolygonalModel *model;
    void drawScene() const;

    void processEvents();

  public:
    ClockApplication();
    ~ClockApplication();

    void mainLoop();
};

#endif  // CLOCK_APPLICATION_HPP
