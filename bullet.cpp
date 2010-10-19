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

#include "bullet.h"

bullet::bullet(playback* PLAY): being::being(vector2d(3.0f, 3.0f), PLAY)
{


}

void bullet::drawShape()
{
  float x1 = -1.0f;
  float y1 = -1.0f;
  float x2 = 1.0f;
  float y2 = 1.0f;
  
  glColor3f(1.0f, 1.0f, 1.0f);
  // glShadeModel(GL_SMOOTH);
  if(condition == LIVING)
    {
      glBegin(GL_QUADS);
      {
	glVertex2f(x1, y1);
	glVertex2f(x2 ,y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
      }
      glEnd();
    }

  if(condition == DYING)
    {
      glScalef(delay*10.0f, delay*10.0f, 0.0f);
      glBegin(GL_QUADS);
      {
	glVertex2f(x1, y1);
	glVertex2f(x2 ,y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
      }
      glEnd();
    }
}

void
bullet::processCollision(object *objCol)
{

  //big mess with collisions.
  //CREATE BETTER TREE, special for this game
  //tide up how collisions should be resolved

  if(typeid(*objCol) == typeid(bullet))
    return;

  if(typeid(*objCol) == typeid(enemy))
    if(objCol -> condition == DEAD)
      return;


  //WITH BLOCK
  //process collision events only once
  if(velocity.x)
    //    if(typeid(*objCol) == typeid(block))
      {

	//bullet blow up on the wall
	if(velocity.x > 0)
	  position.x = objCol -> position.x - objCol -> dimensions.x/2;
	else
	  position.x = objCol -> position.x + objCol -> dimensions.x/2;

	//stop bullet
	velocity = vector2d(0.0f, 0.0f);

      }

  if(condition == LIVING)
    {
      if(typeid(*objCol) == typeid(block))
	{
	  //	  printf("!");
	  	    soundPlayback-> play(2);	
		    condition = DYING;
	}
      

      delay = 0.5f;
    }
}



void
bullet::updateSelf(float deltaTime)
{
  being::updateSelf(deltaTime);
  if(delay < 0.0f)
    condition = DEAD;
}
