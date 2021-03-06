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
#include "object.h"
#include "being.h"
#include <math.h>
#include <typeinfo>
object* object::giveRootObject() {
	if (parentNode)
		return ((object*) parentNode)->giveRootObject();

	return this;
}

void object::draw() {

	//draw itself ...
	drawSelf();

	//draw children ...
	if (HasChild()) {
		((object*) childNode)->draw();
	}

	//draw brothers ...  
	if (HasParent() && !IsLastChild())
		((object*) nextNode)->draw();
}
;

void object::drawSelf() {
	glPushMatrix();
	{
		glTranslatef(position.x, position.y, 0.0f);
		drawShape();
	}
	glPopMatrix();
}

//simply draw rectangular shape ...
//used for terrain blocks
void object::drawShape() {
}

void object::prepare() {
	prepareSelf();

	if (HasChild()) {
		((object*) childNode)->prepare();
	}

	if (HasParent() && !IsLastChild()) {
		((object*) nextNode)->prepare();
	}
}

void object::prepareSelf() {
	//  findCollisions(giveRootObject());
	//  initFindingCollisions();
	printf("--\n");
}

void object::initFindingCollisions() {
	findCollisions(giveRootObject());

	if (HasChild())
		((object*) childNode)->initFindingCollisions();

	if (HasParent() && !IsLastChild())
		((object*) nextNode)->initFindingCollisions();
}

void object::findCollisions(object *objCol) {
	//if difference between positions is smaller or equal
	//to sum of halfs of dimensions
	if ((abs(position.x - objCol->position.x)
			<= (dimensions.x / 2 + objCol->dimensions.x / 2))
			&& (abs(position.y - objCol->position.y)
					<= (dimensions.y / 2 + objCol->dimensions.y / 2)) &&
			//and objCol is not an object itself
			(objCol != ((object*) this)) &&
			//and objCol is not a ghost
			!objCol->ghost) {
		processCollision(objCol);
	}

	if (objCol->HasChild())
		findCollisions((object*) (objCol->childNode));

	if (objCol->HasParent() && !(objCol->IsLastChild()))
		findCollisions((object*) (objCol->nextNode));
}

void object::update(float time) {
	updateSelf(time);

	if (HasChild()) {
		((object*) childNode)->update(time);
	}

	if (HasParent() && !IsLastChild())
		((object*) nextNode)->update(time);
}

void object::updateSelf(float time) {
}

object::object() {
	delay = 0.0f;
	condition = LIVING;
	rotate = 0.0f;
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	acceleration = vector2d(0.0f, 400.0f);
	ghost = false;
}

//for now used only for terrain blocks
object::object(vector2d dim) {
	dimensions = dim;
}

object::~object() {
}

//series of functions defining bouncing box for checking collisions
float object::giveMinX() {
	return position.x - dimensions.x / 2 - 1;
}

float object::giveMaxX() {
	return position.x + dimensions.x / 2 + 1;
}

float object::giveMinY() {
	return position.y - dimensions.y / 2 - 1;
}

float object::giveMaxY() {
	return position.y + dimensions.y / 2 + 1;
}

void object::cleanUp() {

	if (HasChild()) {
		((object*) childNode)->cleanUp();
	}

	if (HasParent() && !IsLastChild())
		((object*) nextNode)->cleanUp();

	if (condition == DEAD) {
		Detach();
	}

}
