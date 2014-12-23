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

#ifndef __BULLET_H
#define __BULLET_H
#include "being.h"
#include "vector.h"
#include <typeinfo>
#include "block.h"
#include "playback.h"

class bullet: public being {
public:

	bullet(playback*);
	void drawShape();
	void processCollision(object*);
	void updateSelf(float deltaTime);
};
#endif
