add_definitions(-Wall -pedantic -O2)

find_package(SDL REQUIRED)
find_package (SDL_image REQUIRED)
if (NOT SDL_FOUND)
    message(FATAL_ERROR "SDL not found!")
endif (NOT SDL_FOUND)

find_package(OpenGL REQUIRED)
if (NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found!")
elseif(NOT OPENGL_GLU_FOUND)
    message(FATAL_ERROR "GLU not found!")
endif (NOT OPENGL_FOUND)

include_directories(${SDL_INCLUDE_DIR})

set(SOURCES
    CompoundModel.cpp
    clock.cpp
    ClockApplication.cpp
    Color.cpp
    GLVertex.cpp
    Material.cpp
    PolygonalModel.cpp
    PerspectiveCamera.cpp
    Position.cpp
    Quaternion.cpp
    Rotation.cpp
    Vector2D.cpp
    Vector3D.cpp
)

add_executable(clock ${SOURCES})
target_link_libraries(clock
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${OPENGL_LIBRARIES}
)
