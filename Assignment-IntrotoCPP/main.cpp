#include <iostream>
#include "myString.h"
#include <cstdlib>
#include <time.h>

using namespace std;

const int MAX_GRID_SIZE = 5;
const int MAX_FLOOR_SIZE = 4;
const int MAX_ENTITY_SIZE = MAX_GRID_SIZE * 2;

void Draw_Grid();

myString word;

int CurrentFloor = 0;

int PlayerHasBeen = 0;

int EntitiesOnFloor = 0;

char RoomGrid[MAX_FLOOR_SIZE][MAX_GRID_SIZE][MAX_GRID_SIZE] = {};

void SetUpEntities();
int RandNum(int);
void Movement();
void EntityChecks();
bool CheckDeath();
void CheckFloor();

struct Player
{
	int xPos = 0;
	int yPos = 0;

	int item_Treasure = 0;

	int Health = 100;

	bool isDead = false;
};

Player player;

int main()
{
	srand(time(0));

	//word.TestFunction();

	player.xPos = rand() % MAX_GRID_SIZE;
	player.yPos = rand() % MAX_GRID_SIZE;

	SetUpEntities();

	while (!player.isDead)
	{
		system("cls");

		Draw_Grid();

		Movement();

		EntityChecks();
	}

	return 0;
}

void Draw_Grid()
{
	//Draws the player in its current position in the map first////----
	RoomGrid[CurrentFloor][player.yPos][player.xPos] = (char)219;

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
			cout << (char)179 << RoomGrid[CurrentFloor][i][j];
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

	for (int i = 0; i < MAX_FLOOR_SIZE; i++)
	{
		for (int j = 0; j < MAX_ENTITY_SIZE; j++)
		{
			RoomGrid[i][RandNum(MAX_GRID_SIZE)][RandNum(MAX_GRID_SIZE)] = (char)63;
		}
	}

	RoomGrid[CurrentFloor][player.yPos][player.xPos] = (char)219;

	for (int i = 0; i < MAX_GRID_SIZE; i++)
	{
		for (int j = 0; j < MAX_GRID_SIZE; j++)
		{
			if (RoomGrid[CurrentFloor][i][j] == (char)63)
			{
				EntitiesOnFloor++;
			}
		}
	}

	PlayerHasBeen = EntitiesOnFloor;
}

int RandNum(int value)
{
	return rand() % value;
}

void Movement()
{
	CheckFloor();

	//Movement
	myString Input;
	cout << "Enter Left, Right, Up, Down to move to different rooms: ";
	Input.ReadFromConsole();

	//Resets current player position
	RoomGrid[CurrentFloor][player.yPos][player.xPos] = (char)176;

	if (Input.EqualTo("left") || Input.EqualTo("a"))
	{
		player.xPos--;
	}
	else if (Input.EqualTo("right") || Input.EqualTo("d"))
	{
		player.xPos++;
	}
	else if (Input.EqualTo("up") || Input.EqualTo("w"))
	{
		player.yPos--;
	}
	else if (Input.EqualTo("down") || Input.EqualTo("s"))
	{
		player.yPos++;
	}
	else
	{
		cout << "Invalid Entry!" << endl;
		system("pause");
	}

	//Make sure player is not outside grid size
	if (player.xPos >= MAX_GRID_SIZE)
	{
		player.xPos--;
	}
	else if (player.xPos < 0)
	{
		player.xPos++;
	}
	else if (player.yPos >= MAX_GRID_SIZE)
	{
		player.yPos--;
	}
	else if (player.yPos < 0)
	{
		player.yPos++;
	}
}

void EntityChecks()
{
	int EntityChooser = 0;

	if (RoomGrid[CurrentFloor][player.yPos][player.xPos] == (char)63)
	{
		PlayerHasBeen--;
		EntityChooser = RandNum(3);
		system("cls");
		Draw_Grid();
	}
	else
	{
		return;
	}

	cout << endl;

	switch (EntityChooser)
	{
	case 0:
	{
			  //Treasure entity
			  cout << "You found some treasure!" << endl;
			  player.item_Treasure++;
	}
		break;
	case 1:
	{
			  //Enemy entity
			  int Damage = RandNum(50);
			  cout << "You battled an enemy and lost " << Damage << " Health." << endl;
			  player.Health -= Damage;
	}
		break;
	case 2:
	{
			  //Nothing of interest
			  cout << "You find nothing of interest in this room." << endl;
	}
		break;
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
		cout << "Floor Complete, You Regain your health back and advance to the next level." << endl;
		system("pause");

		player.Health = 100;

		CurrentFloor++;
		PlayerHasBeen = EntitiesOnFloor;

		system("cls");
		Draw_Grid();
	}
}
