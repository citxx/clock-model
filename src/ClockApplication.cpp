#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "ClockApplication.hpp"
#include "PerspectiveCamera.hpp"
#include "PolygonalModel.hpp"

const int DEFAULT_WINDOW_WIDTH = 600;
const int DEFAULT_WINDOW_HEIGHT = 600;

const int BG_COLOR[] = {1.0, 1.0, 1.0, 1.0};

ClockApplication::ClockApplication():
    windowWidth(DEFAULT_WINDOW_WIDTH),
    windowHeight(DEFAULT_WINDOW_HEIGHT) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        throw (std::string("SDL init error: ") + SDL_GetError()).c_str();
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    this->screen = SDL_SetVideoMode(this->windowWidth, this->windowHeight, 16, SDL_OPENGL | SDL_RESIZABLE);

    if (this->screen == NULL) {
        throw (std::string("SDL Error: ") + SDL_GetError()).c_str();
    }

    this->model = new PolygonalModel("axes.obj");

    glClearColor(BG_COLOR[0], BG_COLOR[1], BG_COLOR[2], BG_COLOR[3]);
    glClearDepth(1.0f);
    glViewport(0, 0, this->windowWidth, this->windowHeight);

    GLfloat light_diffuse[] = {1.0, 1.0, 0.5, 1.0};  /* Red diffuse light. */
    GLfloat light_position[] = {1.5, 1.5, 1.5, 0.0};  /* Infinite light location. */

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    glEnable(GL_DEPTH_TEST);

}

ClockApplication::~ClockApplication() {
    delete this->model;

    SDL_Quit();
}

void ClockApplication::drawScene() {
    PerspectiveCamera cam(
        GLVector(9.0, 4.0, 2.0),
        GLVector(0.0, 0.0, 0.0),
        GLVector(0.0, 0.0, 1.0),
        70.0, 1.0, 1.0, 15.0
    );

    cam.glActivate();

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
    glEnd();

    this->model->glDraw(GLVector(0.0, 0.0, 0.0));
//    this->model->glDraw(GLVector(1.0, 1.0, 1.0));
//    this->model->glDraw(GLVector(2.0, 2.0, 2.0));
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
        }
    }
}

void ClockApplication::mainLoop() {
    this->isRunning = true;
    while (this->isRunning) {
        this->processEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->drawScene();

        SDL_GL_SwapBuffers();
    }
}
