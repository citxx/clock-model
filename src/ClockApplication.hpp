#ifndef CLOCK_APPLICATION_HPP
#define CLOCK_APPLICATION_HPP

#include "CompoundModel.hpp"
#include "PerspectiveCamera.hpp"
#include "PolygonalModel.hpp"
#include "SDL.h"
#include "Vector3D.hpp"

class ClockApplication {
    SDL_Surface *screen;

    int windowWidth;
    int windowHeight;
    bool isRunning;

    PerspectiveCamera mainCamera;

    bool isRotating;
    Vector3D rotateStart;
    Vector3D rotateEnd;
    PerspectiveCamera cameraStart;

    PolygonalModel *stand, *wheel, *secondArrow;
    CompoundModel *clock;
    void buildScene();
    void drawScene();

    void processEvents();

  public:
    ClockApplication();
    ~ClockApplication();

    void mainLoop();
};

#endif  // CLOCK_APPLICATION_HPP
