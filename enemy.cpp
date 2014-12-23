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

#include "enemy.h"
#include "hero.h"
#include "bullet.h"

enemy::enemy(vector2d VEC, playback *PLAYER) :
		being(VEC, PLAYER) {

}

void enemy::updateSelf(float DT) {
	being::updateSelf(DT);

	if (position.y > 1500.0f) {
		condition = DEAD;
	}
}

void enemy::processCollision(object *objCol) {
	float randomSpeed = (rand() % 4 * 100) + 100;

	if (typeid(*objCol) == typeid(block)) {
		//      velocity.x = 400;

		//demonstration part: changing movement
		float oldPosX = this->position.x;
		float oldPosY = this->position.y;

		being::processCollision(objCol);
		//check if coordinates are different as a result of collision
		if (oldPosY > this->position.y && velocity.x == 0) {
			if (rand() % 2)
				velocity.x = randomSpeed;
			else
				velocity.x = -randomSpeed;
		}
		if (oldPosX > this->position.x && velocity.y == 0) {
			velocity.x = -(randomSpeed);
			velocity.y = -(randomSpeed);
		}
		if (oldPosX < this->position.x) {
			velocity.x = randomSpeed;
			velocity.y = -(randomSpeed);
		}
	}

	if (typeid(*objCol) == typeid(bullet))
		if (objCol->condition == LIVING) {
			if (objCol->condition != DYING)
			//	if(condition == LIVING)
					{
				soundPlayback->play(1);
				condition = DEAD;
				objCol->condition = DYING;
			}
		}
}
