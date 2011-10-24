#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL.h"

#include "PolygonalModel.hpp"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        std::cerr << "SDL init error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Surface *screen = SDL_SetVideoMode(640, 640, 16, SDL_OPENGL | SDL_RESIZABLE);

    if (screen == NULL) {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    glClearColor(1, 1, 1, 1);
    glClearDepth(1.0f);
    glViewport(0, 0, 640, 640);

    GLfloat light_diffuse[] = {1.0, 1.0, 0.5, 1.0};  /* Red diffuse light. */
    GLfloat light_position[] = {1.5, 1.5, 1.5, 0.0};  /* Infinite light location. */

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    /* Use depth buffering for hidden surface elimination. */
    glEnable(GL_DEPTH_TEST);

    /* Setup the view of the cube. */
    glMatrixMode(GL_PROJECTION);
    gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 5.0,  // eye is at (0,0,5)
              0.0, 0.0, 0.0,  // center is at (0,0,0)
              0.0, 1.0, 0.0); // up is in positive Y direction

    /* Adjust cube position to be asthetic angle. */
    glTranslatef(0.0, 0.0, -1.0);
    glRotatef(60, 1.0, 0.0, 0.0);
    glRotatef(-20, 0.0, 0.0, 1.0);

    PolygonalModel cube("cyl.obj");

    bool runFlag = true;
    while (runFlag) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                runFlag = false;
            }
            if (event.type == SDL_VIDEORESIZE) {
                screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 16, SDL_OPENGL | SDL_RESIZABLE);
                glViewport(0, 0, event.resize.w, event.resize.h);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        cube.glDraw();

        SDL_GL_SwapBuffers();
    }

    SDL_Quit();

    return 0;
}
