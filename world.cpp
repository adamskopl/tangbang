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
#include "world.h"
#include <sndfile.h>
void world::buildTerrain() {
	int arraySize = 11;
	vector2d *temp = new vector2d[arraySize];

	//create text parser to hold such things
	//like that in plain text (to edit game without
	//compiling code)

	//temp[0] is created to connect hero to it, because
	//collision will not be checked ... fix it - check how tree really works
	temp[0] = vector2d(1.0f, 1000.0f);
	temp[1] = vector2d(500.0f, 1000.0f);
	temp[2] = vector2d(100.0f, 650.0f);
	temp[3] = vector2d(100.0f, 600.0f);
	temp[4] = vector2d(200.0f, 700.0f);
	temp[5] = vector2d(300.0f, 800.0f);
	temp[6] = vector2d(200.0f, 650.0f);
	temp[7] = vector2d(200.0f, 600.0f);
	temp[8] = vector2d(100.0f, 750.0f);
	temp[9] = vector2d(500.0f, 1000.0f);

	//horizontal position for blocks
	float dx = 0;

	block* tempBlock;
	for (int a = 0; a < arraySize; a++) {
		tempBlock = new block(temp[a]);
		tempBlock->position = vector2d(dx + tempBlock->dimensions.x / 2,
				1000.0f - tempBlock->dimensions.y / 2);

		blocks.push_back(tempBlock);
		//horizontal position for next block
		dx += tempBlock->dimensions.x;
	}

	//finding y coordinates of connection points between blocks
	for (int a = 1; a < arraySize; a++) {
		float y1 = blocks[a]->position.y - blocks[a]->dimensions.y / 2;
		float y2 = blocks[a - 1]->position.y - blocks[a - 1]->dimensions.y / 2;
		if (y1 <= y2)
			blocks[a]->eraseY = y2;
		else
			blocks[a]->eraseY = y1;
	}

	for (int a = 0; a < arraySize; a++) {
		blocks[a]->connectTo(root);
	}
}
world::world(int SW, int SH, playback *PLAYBACK) {
	soundPlayback = PLAYBACK;
	newEnemyDelay = 0.0f;

	srand((unsigned) time(0));

	sw = SW;
	sh = SH;

	//  gameTerrain = new terrain(temp, arraySize);
	root = new object();
	root->ghost = true;
	hero = new player(vector2d(20, 20), soundPlayback);

	buildTerrain();

	hero->position.x = (blocks[blocks.size() - 1]->position.x) / 2;
	hero->position.y = -50.0f;
	hero->initPosition = hero->position;

	hero->connectTo(root);
}

void world::prepareWorld() {
	root->initFindingCollisions();
}

void world::updateWorld(float deltaTime) {

	float DT = deltaTime / 1000.0f;

	if (newEnemyDelay > 0.0f)
		newEnemyDelay -= DT;
	else {
		newEnemyDelay = 2.0f;
		createEnemy();
	}

	root->update(DT);
}

void world::cleanUpWorld() {
	root->cleanUp();
}

void world::drawWorld() {
	glClear(GL_COLOR_BUFFER_BIT);

	root->draw();

	//erase vertical lines
	terrainEraseLines();
}

world::~world() {

}

void world::terrainEraseLines() {
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int a = 1; a < blocks.size(); a++) {
		glPushMatrix();
		{
			float x = blocks[a]->position.x - blocks[a]->dimensions.x / 2;
			float y = blocks[a]->eraseY;
			glTranslatef(x, y, 0.0f);
			glBegin(GL_LINES);
			{
				glVertex2f(0.0f, 1.0f);
				glVertex2f(0.0f, 1000.0f);
			}
			glEnd();
		}
		glPopMatrix();
	}
}

void world::createEnemy() {
	newEnemy = new enemy(vector2d(20, 20), soundPlayback);
	newEnemy->position = (blocks[blocks.size() - 1]->position.x) / 2;
	newEnemy->position.y -= 800.0f;
	newEnemy->position.x = rand() % 20 * 100;

	newEnemy->connectTo(root);
}
