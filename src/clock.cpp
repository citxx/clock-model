#include <cstdlib>
#include <iostream>

#include "ClockApplication.hpp"

int main(int argc, char *argv[]) {
    ClockApplication app;
    try {
        app.mainLoop();
    }
    catch (const char *e) {
        std::cerr << "Error: " << e << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
