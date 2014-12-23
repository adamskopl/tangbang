/* 
 This file is part of Tangbang.

 Tangbang is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Tangbang is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Tangbang.  If not, see <http://www.gnu.org/licenses/>.
 */
#include<SDL/SDL.h>
#include<GL/gl.h>
#include<iostream>
#include "node.h"
#include "world.h"
#include "input.h"
#include "timer.h"
#include "camera.h"
#include "playback.h"

using namespace std;

void prepareOpenGL(int sw, int sh) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//specify graphic's screen dimensions
	glViewport(0, 0, sw, sh);
	//choose projection matrix
	glMatrixMode( GL_PROJECTION);
	//reset projection matrix ...
	glLoadIdentity();
	//set ortographical projection (no perspective)
	glOrtho(0, sw, sh, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_DEPTH_TEST);

	//  glEnable(GL_LINE_SMOOTH);
	//  glEnable(GL_POINT_SMOOTH);
	//  glEnable(GL_POLYGON_SMOOTH);
	//  glLineWidth(0.05f);
}

int main(void) {

	int sw = 640;
	int sh = 480;

	SDL_Surface *screen;
	bool loopDone = false;
	SDL_Event event;
	timer *clock;
	camera *gameCamera;
	playback *soundPlayback;

	atexit(SDL_Quit);

	if (-1 == SDL_Init(SDL_INIT_EVERYTHING))
		exit(1);

	soundPlayback = new playback();

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	screen = SDL_SetVideoMode(sw, sh, 0,
	SDL_ANYFORMAT | SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF
	// uncommment for fullscreen
	//|SDL_FULLSCREEN
			);
	prepareOpenGL(sw, sh);

	/////////////////////////////////////////////////////
	clock = new timer();
	world level1(sw, sh, soundPlayback);
	inputSystem *input = new inputSystem(&level1);

	gameCamera = new camera(sw, sh);
	gameCamera->spyMode(level1.hero);
	/////////////////////////////////////////////////////
	while (!loopDone) {
		float timePassed = clock->getTime();
		while (!loopDone && SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_KEYUP: {
				input->onKeyUp(&event.key);
				break;
			}

			case SDL_KEYDOWN: {
				switch (event.key.keysym.sym) {

				case SDLK_ESCAPE: {
					loopDone = true;
					break;
				}

				default: {
					input->onKeyDown(&event.key);
					break;
				}
				}
				break;
			}

			case SDL_JOYAXISMOTION: {
				break;

			}

			case SDL_QUIT: {
				loopDone = true;
				break;
			}
			}
		}

		//change positions
		level1.updateWorld(timePassed);

		//check if in case of changing position collisions occured
		level1.prepareWorld();

		gameCamera->animate(timePassed / 1000.0f);

		level1.drawWorld();
		level1.cleanUpWorld();

		SDL_GL_SwapBuffers();
	}

	return 0;
}
