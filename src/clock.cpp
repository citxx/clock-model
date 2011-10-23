#include <iostream>
#include <cstring>
#include <cstdlib>
#include "SDL.h"
#include <GL/gl.h>
#include <GL/glu.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        std::cerr << "SDL init error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Surface *screen = SDL_SetVideoMode(640, 480, 16, SDL_OPENGL | SDL_RESIZABLE);

    if (screen == NULL) {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    glClearColor(1, 1, 1, 1);
    glClearDepth(1.0f);
    glViewport(0, 0, 640, 480);

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

        SDL_GL_SwapBuffers();
    }

    SDL_Quit();

    return 0;
}
