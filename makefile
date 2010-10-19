#
#   This file is part of Tangbang.
#
#   Tangbang is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Tangbang is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Tangbang.  If not, see <http://www.gnu.org/licenses/>.


CC = g++
CPP_FLAGS = -Wall -g -ggdb
SDL_FLAGS = `sdl-config --libs --cflags` -lSDL -lSDL_image -lSDL_mixer
GL_FLAGS = -I/usr/X11R6/include -L/usr/X11R6/lib -lGL -lGLU
OBJ = main.o node.o object.o being.o world.o input.o\
      timer.o camera.o block.o playback.o hero.o bullet.o\
      enemy.o


game: ${OBJ}
	g++ ${CPP_FLAGS} ${SDL_FLAGS} ${GL_FLAGS} ${OBJ} -o demo

main.o : main.cpp input.h input.cpp
	g++ ${CPP_FLAGS} ${GL_FLAGS} -c main.cpp

node.o: node.cpp node.h world.cpp world.h
	g++ ${CPP_FLAGS} -c node.cpp

object.o: object.cpp object.h vector.h node.h node.cpp
	g++ ${CPP_FLAGS} -c object.cpp

being.o: being.cpp being.h object.h object.cpp
	g++ ${CPP_FLAGS} -c being.cpp

world.o : world.cpp world.h being.h being.cpp
	g++ ${CPP_FLAGS} -c world.cpp

input.o : input.cpp input.h world.h world.cpp
	g++ -ggdb -g -c input.cpp

timer.o : timer.cpp timer.h
	g++ ${CPP_FLAGS} -c timer.cpp

camera.o : camera.cpp camera.h
	g++ ${CPP_FLAGS} -c camera.cpp

block.o : block.cpp block.h object.h object.cpp
	g++ ${CPP_FLAGS} -c block.cpp

playback.o : playback.cpp playback.h
	g++ ${CPP_FLAGS} -c playback.cpp

hero.o : hero.cpp hero.h
	g++ ${CPP_FLAGS} -c hero.cpp

bullet.o: bullet.cpp bullet.h
	g++ ${CPP_FLAGS} -c bullet.cpp

enemy.o: enemy.cpp enemy.h
	g++ ${CPP_FLAGS} -c enemy.cpp

clean:
	rm ${OBJ}
