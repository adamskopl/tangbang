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
#ifndef __CAMERA_H
#define __CAMERA_H

#include "vector.h"
#include "object.h"

//Kingpig, lookout here ...
//class object;

class camera {
public:
	vector2d speed;
	vector2d accel;

	float rotateX, rotateY, rotateZ;

	//actual, final position and difference between them
	vector2d posA, posB;
	//values for manipulating speed and acceleration
	float speedInter, accelInter;
	//difference between positions
	vector2d posDiff;

	//actual and final rotation around actor
	float rotActA, rotActB;
	float rotSpeed, rotAccel;
	//values for manipulating rotation's speed and acceleration
	float rotSpeedInter, rotAccelInter;
	//difference between rotatations
	float rotDiff;

	//how far from actor?
	float distance;
	float camHeight;
	//calculate new values
	void updateRotation(float);
	void updatePosition(float);

	//screen's dimenstions
	int sw, sh;

	camera(int, int);
	~camera();

	//1)mimeMode - follows object without delay
	void mimeMode(object*);

	//2)spyMode - follows object with delay
	void spyMode(object*);

	//target of actual camera's mode
	object *actor;
	//which mode is on ?
	int modeId;

	void animate(float deltaTime);
};

#endif
