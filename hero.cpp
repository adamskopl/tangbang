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

#include "hero.h"

player::player(vector2d VEC, playback *PLAYER) :
		being(VEC, PLAYER) {
	gunRotate = -110.0f;
	direction = 1.0f;
}

void player::drawShape() {

	//points for quad
	float x1 = -dimensions.x / 2;
	float y1 = dimensions.y / 2;
	float x2 = dimensions.x / 2;
	float y2 = -dimensions.y / 2;

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(0.0f, y2);
		glVertex2f(x2, y1);
		glVertex2f(x1, y1);
	}
	glEnd();

	//if hero is faced left, draw gun in "mirror X-axis"
	if (direction < 0.0f)
		glScalef(-1.0f, 1.0f, 0.0f);

	glTranslatef(-5.0, 3.0f, 0.0f);

	drawGun();
}

void player::drawGrip() {
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(-2.0f, -2.5f);
		glVertex2f(2.0f, -2.5f);
		glVertex2f(2.0f, 2.5f);
		glVertex2f(-2.0f, 2.5f);
	}
	glEnd();

}
void player::drawSlide() {
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(-6.0f, -3.5f);
		glVertex2f(6.0f, -3.5f);
		glVertex2f(6.0f, 3.5f);
		glVertex2f(-6.0f, 3.5f);
	}
	glEnd();
}

void player::drawBarrel() {
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(-1.0f, -1.0f);
		glVertex2f(1.0f, -1.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(-1.0f, 1.0f);
	}
	glEnd();
}

void player::drawGun() {
	glRotatef(gunRotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(3.0f, 0.0f, 0.0f);

	drawGrip();

	glTranslatef(2.5f, -6.0f, 0.0f);
	drawSlide();

	glTranslatef(8.0f, 0.0f, 0.0f);
	drawBarrel();

}

void player::shoot() {
	shot = new bullet(soundPlayback);

	shot->position = position;
	if (direction < 0) {
		shot->position.x -= 3.0f;
		shot->velocity.x = -800.0f + velocity.x;
	} else {
		shot->position.x += 3.0f;
		shot->velocity.x = 800.0f + velocity.x;
	}

	shot->velocity.y = 0.0f;
	shot->acceleration.x = 0.0f;
	shot->acceleration.y = 0.0f;

	shot->AttachTo(this);
}

void player::updateSelf(float DT) {

	being::updateSelf(DT);

	if (position.y > 1500.0f) {
		position = initPosition;
		velocity.y = 0.0f;
		soundPlayback->play(4);
	}

}

void player::processCollision(object *objCol) {

	//COLISION TYPE

	//WITH BLOCK
	if (typeid(*objCol) == typeid(block)) {
		//move back
		being::processCollision(objCol);
		//      printf("player hits block!\n");
	}

	//WITH ENEMY
	if (typeid(*objCol) == typeid(enemy)) {
		position = initPosition;
		velocity.y = 0.0f;
		soundPlayback->play(4);
	}

}
