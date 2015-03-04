#include "Room.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>

using namespace std;


void Room::RoomChooser(Player &player)
{
	int RoomType = rand() % 3;

	switch (RoomType)
	{
		case 0:
		{
				  //Treasure entity
				  cout << endl << "You found some treasure!" << endl << endl;
				  player.item_Treasure++;
		} break;
		case 1:
		{
				  //Enemy entity
				  int Damage = rand() % 50;
				  cout << endl << "You battled an enemy and lost " << Damage << " Health." << endl << endl;
				  player.Health -= Damage;
		} break;
		case 2:
		{
				  //Nothing of interest
				  cout << endl << "You find nothing of interest in this room." << endl << endl;
		} break;
	}
}