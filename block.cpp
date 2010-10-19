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
#include "block.h"
#include <typeinfo>
#include "bullet.h"

void 
block::drawShape()
{

  glColor3f(0.5f, 0.5f, 0.5f);

  float x1 = -dimensions.x/2;
  float y1 = -dimensions.y/2;
  float x2 = dimensions.x/2;
  float y2 = dimensions.y/2;

  glBegin(GL_LINE_LOOP);
  {
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2); 
  }
  glEnd();
}

void 
block::prepareSelf()
{

}

block::block(vector2d DIM)
{
  dimensions = DIM;
}

void
block::processCollision(object* objCol)
{
  //blocks are tough ... they just stand!
  //  printf("block hits something\n");
}
