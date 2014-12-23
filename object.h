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
#ifndef __OBJECT_H
#define __OBJECT_H

#include "vector.h"
#include "tree.h"
#include <SDL/SDL.h>
#include <GL/gl.h>

enum cond {
	DEAD, DYING, LIVING
};

class object: public CNode {

public:
	vector2d position;
	vector2d velocity;
	vector2d acceleration;

	vector2d dimensions;
	int rotate;
	enum cond condition;

	//if true don't check collisions
	bool ghost;
	float delay;

	object* giveRootObject();

	virtual void draw();
	void drawSelf();
	virtual void drawShape();

	/////////////  COLLISIONS   /////////////////
	void initFindingCollisions();
	void findCollisions(object*);
	virtual void processCollision(object *) {
	}
	;
	////////////////////////////////////////////

	void prepare();
	void update(float time);
	void cleanUp();

	virtual void updateSelf(float Time);
	virtual void prepareSelf();

	float giveMinX();
	float giveMaxX();
	float giveMinY();
	float giveMaxY();

	object();
	object(vector2d);
	~object();

};

#endif
