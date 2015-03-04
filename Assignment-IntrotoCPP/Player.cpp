#include "Player.h"
#include "Room.h"
#include "myString.h"
#include "Globals.h"
#include <iostream>

using namespace std;

void Player::Movement(void (*CheckFloor)(), char RoomGrid[][MAX_GRID_SIZE][MAX_GRID_SIZE], int &CurrentFloor)
{
	CheckFloor();

	//Movement
	myString Input;
	cout << "Enter Left, Right, Up, Down to move to different rooms: ";
	Input.ReadFromConsole();
	Input.ToLower();

	//Sets the player path
	RoomGrid[CurrentFloor][yPos][xPos] = (char)176;

	if (Input.EqualTo("left") || Input.EqualTo("a"))
	{
		if (RoomGrid[CurrentFloor][yPos][xPos - 1] != (char)219)
		{
			xPos--;
		}
	}
	else if (Input.EqualTo("right") || Input.EqualTo("d"))
	{
		if (RoomGrid[CurrentFloor][yPos][xPos + 1] != (char)219)
		{
			xPos++;
		}
	}
	else if (Input.EqualTo("up") || Input.EqualTo("w"))
	{
		if (RoomGrid[CurrentFloor][yPos - 1][xPos] != (char)219)
		{
			yPos--;
		}
	}
	else if (Input.EqualTo("down") || Input.EqualTo("s"))
	{
		if (RoomGrid[CurrentFloor][yPos + 1][xPos] != (char)219)
		{
			yPos++;
		}
	}
	else
	{
		cout << "Invalid Entry!" << endl;
		system("pause");
	}

	//Make sure player is not outside grid size
	if (xPos >= MAX_GRID_SIZE)
	{
		xPos--;
	}
	else if (xPos < 0)
	{
		xPos++;
	}
	else if (yPos >= MAX_GRID_SIZE)
	{
		yPos--;
	}
	else if (yPos < 0)
	{
		yPos++;
	}
}