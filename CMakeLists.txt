cmake_minimum_required (VERSION 2.6)
project (tangbang)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(tangbang being.cpp block.cpp bullet.cpp camera.cpp
  enemy.cpp hero.cpp input.cpp main.cpp object.cpp playback.cpp
  timer.cpp world.cpp)

find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_mixer REQUIRED)

target_link_libraries(tangbang ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}
${SDL_LIBRARY} ${SDL_MIXER_LIBRARY} )

install (TARGETS tangbang DESTINATION bin)