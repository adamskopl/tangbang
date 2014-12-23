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
#include "being.h"
#include "block.h"
#include "hero.h"
#include <typeinfo>

being::being(vector2d DIM, playback* PLAYBACK) {
	soundPlayback = PLAYBACK;
	dimensions = DIM;
}

being::~being() {

}

void being::drawShape() {
	//points for quad
	float x1 = -dimensions.x / 2;
	float y1 = dimensions.y / 2;
	float x2 = dimensions.x / 2;
	float y2 = -dimensions.y / 2;

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
	}
	glEnd();

}

void being::prepareSelf() {
}

void being::updateSelf(float deltaTime) {
	this->deltaTime = deltaTime;
	position += velocity * deltaTime;
	velocity += acceleration * deltaTime;

	if (delay > 0)
		delay -= deltaTime;

	//  printf("%f\n", position.y);

}

void being::processCollision(object *objCol) {
	//difference between objects - to reduce positions
	float diffX, diffY;
	diffX = 0;
	diffY = 0;

	//when you are a being and you are hitting wall
	//you have to move back :-)
	if (typeid(*objCol) == typeid(block)) {
		//only when hitting in walls coordination's changes are necessary

		//if moving in right direction
		if (velocity.x > 0) {
			//if wall's left vertical line is between being's vertical lines
			if (giveMaxX() >= objCol->giveMinX()
					&& giveMinX() < objCol->giveMinX())
				diffX = objCol->giveMinX() - giveMaxX() + 1;
		} else
		//if moving in left direction
		if (velocity.x < 0) {
			//if wall's right vertical line is between being's vertical lines
			if (giveMinX() <= objCol->giveMaxX()
					&& giveMaxX() > objCol->giveMaxX())
				diffX = objCol->giveMaxX() - giveMinX() - 1;
		}

		//wall's horizontal line is between being's horizontal lines
		if (giveMaxY() >= objCol->giveMinY()
				&& giveMinY() < objCol->giveMinY()) {
			diffY = objCol->giveMinY() - giveMaxY() + 1;
		}

		if (diffX) {
			position.x += diffX;
			if (typeid(this) == typeid(enemy)) {
				this->velocity.x = -(this->velocity.x);
			}
		}

		if (diffY) {
			velocity.y = 0;
			position.y += diffY;
		}
	}
}

