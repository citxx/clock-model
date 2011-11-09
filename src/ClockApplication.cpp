#include <cmath>
#include <ctime>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "ClockApplication.hpp"
#include "PolygonalModel.hpp"

const int DEFAULT_WINDOW_WIDTH = 600;
const int DEFAULT_WINDOW_HEIGHT = 600;

// Camera parameters
const Vector3D DEFAULT_LOCATION = Vector3D(20.0, 0.0, 15.0);
const Vector3D DEFAULT_CENTER = Vector3D(0.0, 0.0, 7.5);
const Vector3D DEFAULT_UP = Vector3D (0.0, 0.0, 0.1);
const float DEFAULT_VIEW_ANGLE = 60.0;
const float DEFAULT_NEAR_PLANE = 1.0;
const float DEFAULT_FAR_PLANE = 50.0;

const float DISTANCE_DIFF = 0.9;

const int BG_COLOR[] = {1.0, 1.0, 1.0, 1.0};

const float WHEEL_SPEED = 0.1;  // Rotations per second

ClockApplication::ClockApplication():
    windowWidth(DEFAULT_WINDOW_WIDTH),
    windowHeight(DEFAULT_WINDOW_HEIGHT),
    isRunning(false),
    mainCamera(
        DEFAULT_LOCATION,
        DEFAULT_CENTER,
        DEFAULT_UP,
        DEFAULT_VIEW_ANGLE,
        (float)DEFAULT_WINDOW_WIDTH / DEFAULT_WINDOW_HEIGHT,
        DEFAULT_NEAR_PLANE,
        DEFAULT_FAR_PLANE
    ),
    isRotating(false),
    cameraStart(mainCamera) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        throw (std::string("SDL init error: ") + SDL_GetError()).c_str();
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    this->screen = SDL_SetVideoMode(this->windowWidth, this->windowHeight, 16, SDL_OPENGL | SDL_RESIZABLE);

    if (this->screen == NULL) {
        throw (std::string("SDL Error: ") + SDL_GetError()).c_str();
    }

    this->stand = new PolygonalModel("models/stand.obj");
    this->wheel = new PolygonalModel("models/wheel.obj");
    this->secondArrow = new PolygonalModel("models/secondArrow.obj");
    this->minuteArrow = new PolygonalModel("models/minuteArrow.obj");
    this->hourArrow = new PolygonalModel("models/hourArrow.obj");
    this->clock = NULL;

    glClearColor(BG_COLOR[0], BG_COLOR[1], BG_COLOR[2], BG_COLOR[3]);
    glClearDepth(1.0f);
    glViewport(0, 0, this->windowWidth, this->windowHeight);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

ClockApplication::~ClockApplication() {
    delete this->stand;
    delete this->wheel;
    delete this->secondArrow;
    delete this->minuteArrow;
/*    if (this->model != NULL) {
        delete this->model;
    }
*/
    SDL_Quit();
}

void ClockApplication::buildScene() {
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    int seconds = localTime->tm_sec;
    int minutes = localTime->tm_min;
    int hours = localTime->tm_hour;
    float realMinutes = minutes + seconds / 60.0;
    float realHours = hours + realMinutes / 60.0;

    float abstractMilliseconds = SDL_GetTicks();
    float abstractSeconds = abstractMilliseconds / 1000.0;

    if (this->clock != NULL) {
        delete this->clock;
    }

    std::vector <Model *> models;
    std::vector <Position> positions;

    models.push_back(this->stand);
    positions.push_back(Position(
        Vector3D(0.0, 0.0, 0.0)
    ));

    models.push_back(this->wheel);
    positions.push_back(Position(
        Vector3D(0.0, 0.0, 9.0),
        Rotation(WHEEL_SPEED * abstractSeconds * 2 * M_PI, Vector3D(-1.0, 0.0, 0.0))
    ));

    models.push_back(this->secondArrow);
    positions.push_back(Position(
        Vector3D(3.85, 0.0, 7.5),
        Rotation(seconds / 60.0 * 2 * M_PI, Vector3D(-1.0, 0.0, 0.0))
    ));

    models.push_back(this->minuteArrow);
    positions.push_back(Position(
        Vector3D(3.73, 0.0, 7.5),
        Rotation(minutes / 60.0 * 2 * M_PI, Vector3D(-1.0, 0.0, 0.0))
    ));

    std::cerr << realHours << std::endl;
    models.push_back(this->hourArrow);
    positions.push_back(Position(
        Vector3D(3.79, 0.0, 7.5),
        Rotation(realHours / 12.0 * 2 * M_PI, Vector3D(-1.0, 0.0, 0.0))
    ));

    this->clock = new CompoundModel(models, positions);
}

void ClockApplication::drawScene() {
    this->mainCamera.glActivate();

    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {4.0, 7.0, 10.0, 0.0};  /* Infinite light location. */

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(10.0, 0.0, 0.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 10.0, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 10.0);
        glColor3f(0.5, 0.5, 0.5);
    glEnd();

    this->clock->glDraw(Position(Vector3D(0.0, 0.0, 0.0)));
}

void ClockApplication::processEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            this->isRunning = false;
        }
        if (event.type == SDL_VIDEORESIZE) {
            this->windowWidth = event.resize.w;
            this->windowHeight = event.resize.h;
            this->screen = SDL_SetVideoMode(this->windowWidth, this->windowHeight, 16, SDL_OPENGL | SDL_RESIZABLE);
            glViewport(0, 0, this->windowWidth, this->windowHeight);
            this->mainCamera = this->mainCamera.resized(this->windowWidth, this->windowHeight);
        }
        if (event.type == SDL_MOUSEMOTION) {
            if (this->isRotating) {
//                std::cerr << "Moving" << std::endl;
                this->rotateEnd = Vector3D(event.motion.x, event.motion.y);
            }
//            printf("Mouse moved by %d,%d to (%d,%d)\n",
//                   event.motion.xrel, event.motion.yrel,
//                   event.motion.x, event.motion.y);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_RIGHT) {
                this->isRotating = true;
                this->rotateStart = Vector3D(event.button.x, event.button.y);
                this->rotateEnd = this->rotateStart;
                this->cameraStart = this->mainCamera;
            }
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_RIGHT) {
                this->isRotating = false;
            }
        }
/*        if (event.type == 4) {
            this->mainCamera = this->mainCamera.redistanted(DISTANCE_DIFF);
        }
        if (event.type == 5) {
            this->mainCamera = this->mainCamera.redistanted(1.0 / DISTANCE_DIFF);
        }*/
    }

    // TODO: Calculate new camera position
    if (this->isRotating) {
        Vector3D move = this->rotateEnd - this->rotateStart;
        float alpha = 2 * move.x / this->windowHeight * DEFAULT_VIEW_ANGLE;
        float betha = 2 * move.y / this->windowHeight * DEFAULT_VIEW_ANGLE;

        this->mainCamera = this->cameraStart.rotated(alpha, -betha);
    }
}

void ClockApplication::mainLoop() {
    this->isRunning = true;
    while (this->isRunning) {
        this->processEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->buildScene();
        this->drawScene();

        SDL_GL_SwapBuffers();
    }
}
