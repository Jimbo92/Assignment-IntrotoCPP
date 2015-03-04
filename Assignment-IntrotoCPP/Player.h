#include "Globals.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:

	void Movement(void (*CheckFloor)(), char RoomGrid[][MAX_GRID_SIZE][MAX_GRID_SIZE], int &CurrentFloor);

	int xPos = 0;
	int yPos = 0;

	int item_Treasure = 0;

	int Health = 100;

	bool isDead = false;


};

#endif // !PLAYER_H
