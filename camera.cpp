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
#include "camera.h"
#include <GL/gl.h>

camera::camera(int SW, int SH) {
	sw = SW;
	sh = SH;
}

void camera::spyMode(object *actor) {
	this->actor = actor;

	posA = vector2d(actor->position.x, actor->position.y);

	posB = posA;
	posDiff = vector2d(0.0f, 0.0f);

	speedInter = 3.0f;
	accelInter = 2.0f;

	modeId = 1;
}

void camera::updatePosition(float deltaTime) {
	//final position is equal to actor's position
	posB = actor->position;

	vector2d tempDiff = posB - posA;

	if (posDiff != tempDiff) {
		posDiff = tempDiff;
		speed = posDiff * speedInter;
		accel = -posDiff * accelInter;
	}

	speed += accel * deltaTime;
	posA += speed * deltaTime;
}

void camera::animate(float deltaTime) {
	glLoadIdentity();

	switch (modeId) {
	case (1): {
		//dont't know why, but updatePosition works
		//wrong, when placed here in other game
		updatePosition(deltaTime);

		//setting world's objects positions will
		//depend on actor's position

		//NOTE - change posB into posA to have delay
		float camX = -(posA.x);
		float camY = -(posA.y);
		//from now on every translation will be started
		//from vector (-heroPos.x + sw/2, -heroPos.y + sh/2)
		//so for example heor's position will be right in 
		//center of a screen

		glTranslatef(camX + sw / 2, camY + sh / 2, 0.0f);

		break;
	}
	default: {
		//error about wrong camera mode ..
	}
	}
}
