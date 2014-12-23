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

#ifndef __PLAYBACK_H
#define __PLAYBACK_H
#include <SDL/SDL_mixer.h>

class playback {
	int audio_rate;			//Frequency of audio playback
	Uint16 audio_format; 	//Format of the audio we're playing
	int audio_channels;			//2 channels = stereo
	int audio_buffers;		//Size of the audio buffers in memory

	int soundsAmount;
	int *channels;
	Mix_Chunk *sndBoom01;
	Mix_Chunk *sndBoom02;
	Mix_Chunk *sndBoom03;
	Mix_Chunk *sndColl01;
	Mix_Chunk *sndGameOver;
	Mix_Chunk *sndJump;
	Mix_Chunk *sndShoot01;
	Mix_Chunk *sndShoot02;
public:
	playback();
	~playback();

	void play(int);

};

#endif
