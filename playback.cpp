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

#include "playback.h"


playback::playback()
{
  audio_rate = 22050;			//Frequency of audio playback
  audio_format = AUDIO_S16SYS; 	//Format of the audio we're playing
  audio_channels = 2;			//2 channels = stereo
  audio_buffers = 4096;		//Size of the audio buffers in memory

  soundsAmount = 8;
  channels = new int[soundsAmount];
  //Initialize SDL_mixer with our chosen audio settings
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
    printf("Unable to initialize audio: %s\n", Mix_GetError());
  }

  sndBoom01 = Mix_LoadWAV("sounds/boom01.wav");    //0
  sndBoom02 = Mix_LoadWAV("sounds/boom02.wav");    //1
  sndBoom03 = Mix_LoadWAV("sounds/boom03.wav");    //2
  sndColl01 = Mix_LoadWAV("sounds/coll01.wav");    //3
  sndGameOver = Mix_LoadWAV("sounds/gameOver.wav");//4
  sndJump = Mix_LoadWAV("sounds/jump.wav");        //5
  sndShoot01 = Mix_LoadWAV("sounds/shoot02.wav");  //6
  sndShoot02 = Mix_LoadWAV("sounds/shoot02.wav");  //7
    

}

void 
playback::play(int sound)
{
  switch(sound)
    {
    case(0):
      {
	channels[0] = Mix_PlayChannel(-1, sndBoom01, 0);
	
	break;
      }
    case(1):
      {
	channels[1] = Mix_PlayChannel(-1, sndBoom02, 0);
	break;
      }
    case(2):
      {
	channels[2] = Mix_PlayChannel(-1, sndBoom03, 0);
	break;
      }
    case(3):
      {
	channels[3] = Mix_PlayChannel(-1, sndColl01, 0);
	break;
      }
    case(4):
      {
	channels[4] = Mix_PlayChannel(-1, sndGameOver, 0);
	break;
      }
    case(5):
      {
	channels[5] = Mix_PlayChannel(-1, sndJump, 0);
	break;
      }
    case(6):
      {
	channels[6] = Mix_PlayChannel(-1, sndShoot01, 0);
	break;
      }
    case(7):
      {
	break;
      }
      
    }
  
}

playback::~playback()
{
  Mix_CloseAudio();
}
