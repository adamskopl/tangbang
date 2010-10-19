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
#ifndef __WORLD_H
#define __WORLD_H

#include "being.h"
#include <SDL/SDL.h>
#include <vector>
#include "timer.h"
#include "block.h"
#include "playback.h"
#include "hero.h"
#include "enemy.h"

class world
{
 public:

  object *root;
  int sw, sh;
  playback* soundPlayback;
  

  player *hero;
  enemy *newEnemy;
  
  void drawWorld();
  void prepareWorld();
  void updateWorld(float deltaTime);
  void cleanUpWorld();
  void buildTerrain();
  void terrainEraseLines();

  vector <block*> blocks;
  world(int, int, playback*);
  ~world();

  float newEnemyDelay;
  void createEnemy();
};

#endif
