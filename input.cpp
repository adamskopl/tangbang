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
#include "input.h"
#define hero servedWorld -> hero//for shorter code

inputSystem::inputSystem(world* WORLD)
{
  servedWorld = WORLD;
  SDL_ShowCursor(SDL_DISABLE);
  SDL_EnableKeyRepeat(20,1);

  js = SDL_JoystickOpen(0);
  if(js == NULL)
    printf("No joystick detected\n");

  
}

void inputSystem::onKeyUp(SDL_KeyboardEvent *key)
{
  switch(key->keysym.sym){

  case SDLK_a:
    {
      //      if(hero -> velocity.y == 0)
      hero -> velocity.x = 0;
      break;
    }

  case SDLK_d:
    {
      //      if(hero -> velocity.y ==0)
      hero -> velocity.x = 0;
      break;
    }

  case SDLK_j:
    {
      hero -> gunRotate = -110.0f;
    }
  }
}

void inputSystem::onKeyDown(SDL_KeyboardEvent *key)
{
  switch(key->keysym.sym){

    //go left
  case SDLK_a:
    {
      if (hero -> velocity.x == 0)
	hero -> velocity.x = -400.0f;

      hero -> direction = -1.0f;
      break;
    }

    //go right
  case SDLK_d:
    {
      if (hero -> velocity.x == 0)
	hero -> velocity.x = 400.0f;

      hero -> direction = 1.0f;
      break;
    }

    //jump
  case SDLK_k:
    {
      //hero can jump only if he's not moving vertivally
      if(hero -> velocity.y == 0)
	{
	  hero -> soundPlayback -> play(5);
	  hero -> velocity.y = -400.0f;
	}
      break;
    }
  case SDLK_j:
    {
      hero -> gunRotate = 0.0f;

      if(hero->delay <= 0.0f)
	{
	  hero -> soundPlayback -> play(6);
	  hero -> shoot();
	  hero -> delay = 0.3f;
	}
      break;
    }

  }
}

inputSystem::~inputSystem()
{
  SDL_JoystickClose(0);
}
