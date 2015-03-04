#include <iostream>
#include "myString.h"
#include <cstdlib>
#include <time.h>
#include "Player.h"
#include "Room.h"
#include "Globals.h"

using namespace std;

void Draw_Grid();

myString word;

int CurrentFloor = 0;

int PlayerHasBeen = 0;

int EntitiesOnFloor();

char RoomGrid[MAX_FLOOR_SIZE][MAX_GRID_SIZE][MAX_GRID_SIZE] = {};

void SetUpEntities();
int RandNum(int);
void EntityChecks();
bool CheckDeath();
void CheckFloor();


Player player;
Room room;

int main()
{
	srand(time(0));

	//word.TestFunction();

	SetUpEntities();

	while (!player.isDead)
	{
		system("cls");

		Draw_Grid();

		player.Movement(&CheckFloor, RoomGrid, CurrentFloor);

		EntityChecks();
	}

	return 0;
}

void Draw_Grid()
{
	//Draws the player in its current position in the map first////----
	RoomGrid[CurrentFloor][player.yPos][player.xPos] = (char)127;

	//Draw Floor Number
	if (CurrentFloor < 1)
	{
		cout << "Ground Floor" << endl;
	}
	else if (CurrentFloor >= 1 && CurrentFloor < MAX_FLOOR_SIZE)
	{
		cout << "Floor " << CurrentFloor << endl;
	}
	else
	{
		cout << "Top Floor" << endl;
	}

	//Draws a pretty grid
	cout << (char)218 << (char)196 << (char)194;

	for (int i = 0; i < MAX_GRID_SIZE - 2; i++)
	{
		cout << (char)196 << (char)194;
	}

	cout << (char)196 << (char)191 << endl;

	for (int i = 0; i < MAX_GRID_SIZE; i++)
	{
		for (int j = 0; j < MAX_GRID_SIZE; j++)
		{
			//Check for rooms around player and draw player and has been path
			if (player.xPos + 1 == j && player.yPos == i
				|| player.xPos - 1 == j && player.yPos == i
				|| player.yPos + 1 == i && player.xPos == j
				|| player.yPos - 1 == i && player.xPos == j
				|| RoomGrid[CurrentFloor][i][j] == (char)127
				|| RoomGrid[CurrentFloor][i][j] == (char)176
				|| RoomGrid[CurrentFloor][i][j] == (char)219)
			{
				cout << (char)179 << RoomGrid[CurrentFloor][i][j];
			}
			else
			{
				cout << (char)179 << (char)32;
			}
		}

		cout << (char)179;

		//Draw Player Info
		if (i == 1)
		{
			cout << "	Player HP: " << player.Health;
		}
		else if (i == 2)
		{
			cout << "	Treasures: " << player.item_Treasure;
		}
		else if (i == 0)
		{
			cout << "	Rooms of Interest remain: " << PlayerHasBeen;
		}

		cout << endl;

		if (i < MAX_GRID_SIZE - 1)
		{
			cout << (char)195 << (char)196;
		}
		else
		{
			cout << (char)192 << (char)196;
		}

		if (i < MAX_GRID_SIZE - 1)
		{
			for (int o = 0; o < MAX_GRID_SIZE - 1; o++)
			{
				cout << (char)197 << (char)196;
			}

			cout << (char)180 << endl;
		}
		else
		{
			for (int o = 0; o < MAX_GRID_SIZE - 1; o++)
			{
				cout << (char)193 << (char)196;
			}

			cout << (char)217 << endl;
		}
	}
}

void SetUpEntities()
{
	//Sets up the world map entities

	for (int j = 0; j < MAX_ENTITY_SIZE; j++)
	{
		RoomGrid[CurrentFloor][RandNum(MAX_GRID_SIZE)][RandNum(MAX_GRID_SIZE)] = (char)63;
	}

	//Blocked rooms
	int wallType = RandNum(2);

	int RandX = RandNum(MAX_GRID_SIZE);
	int RandY = RandNum(MAX_GRID_SIZE);

	for (int j = 0; j < MAX_ENTITY_SIZE / 3; j++)
	{
		if (RandX + j < MAX_GRID_SIZE && RandY + j < MAX_GRID_SIZE && RandX + j >= 0 && RandY + j >= 0)
		{
			if (wallType == 1)
			{
				RoomGrid[CurrentFloor][RandY][RandX + j] = (char)219;
			}
			else
			{
				RoomGrid[CurrentFloor][RandY + j][RandX] = (char)219;
			}
		}
	}

	player.xPos = rand() % MAX_GRID_SIZE;
	player.yPos = rand() % MAX_GRID_SIZE;

	RoomGrid[CurrentFloor][player.yPos][player.xPos] = (char)219;

	PlayerHasBeen = EntitiesOnFloor();
}

int RandNum(int value)
{
	return rand() % value;
}

void EntityChecks()
{
	int EntityChooser = 0;

	if (RoomGrid[CurrentFloor][player.yPos][player.xPos] == (char)63)
	{
		PlayerHasBeen--;

		system("cls");
		room.RoomChooser(player);
		Draw_Grid();
	}
	else
	{
		return;
	}


	player.isDead = CheckDeath();

	system("pause");
}

bool CheckDeath()
{
	//Check if the player is dead
	if (player.Health <= 0)
	{
		player.Health = 0;

		cout << "You Died!" << endl << "Game Over." << endl;
		system("pause");
		return true;
	}
	return false;
}

void CheckFloor()
{
	if (PlayerHasBeen <= 0)
	{
		cout << endl << "Floor Complete, You Regain your health back and advance to the next level." << endl << endl;
		system("pause");

		player.Health = 100;

		CurrentFloor++;
		SetUpEntities();

		system("cls");
		Draw_Grid();
	}
}

int EntitiesOnFloor()
{
	int value = 0;

	for (int i = 0; i < MAX_GRID_SIZE; i++)
	{
		for (int j = 0; j < MAX_GRID_SIZE; j++)
		{
			if (RoomGrid[CurrentFloor][j][i] == (char)63)
			{
				value++;
			}
		}
	}

	return value;
}
