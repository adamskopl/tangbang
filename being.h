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
#ifndef __BEING_H
#define __BEING_H

#include "object.h"
#include <SDL/SDL.h>
#include "playback.h"
#include <iostream>
#include <string>

using namespace std;

class being: public object {
public:

	vector2d initPosition;
	playback *soundPlayback;

	float deltaTime;
	being(vector2d, playback*);
	~being();

	//  void drawSelf();
	void drawShape();

	void prepareSelf();
	void updateSelf(float time);
	void processCollision(object*);
};

#endif
