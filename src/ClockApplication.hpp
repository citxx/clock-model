#ifndef CLOCK_APPLICATION_HPP
#define CLOCK_APPLICATION_HPP

#include "GLVector.hpp"
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
    GLVector rotateStart;
    GLVector rotateEnd;
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
