#include "GameState.h"
#include <iostream>
#include "string.h"
#include <random>
#include <ctime>
#include <cstdlib>
#include "sfwdraw.h"

using namespace game;
using namespace std;

game::player::player(void)
{
	currentRoom = Randint(0, 19);
	
}

void game::player::update()
{
	cout << "Your current room is " << currentRoom << endl;
	cout << "This room leads to " << room[currentRoom].getRoom1().getRoomID() << endl;
	cout << "This room leads to " << room[currentRoom].getRoom2().getRoomID() << endl;
	cout << "This room leads to " << room[currentRoom].getRoom3().getRoomID() << endl;

	int choice;

	cout << "Input 1 to shoot" << endl;
	cout << "Input 2 to move" << endl;
	cout << "Input 3 to exit" << endl;

	cin >> choice;

	switch (choice)
	{
	case 1:
	case 2:
		movement(); break;
	case 3: break;
	}

}

int game::player::getArrowCount()
{
	return arrow_count;
}

bool game::player::shootArrow()
{
	return false;
}

void game::player::movement()
{
	int move;
	cout << "Press 1 to move to room " << room[currentRoom].getRoom1().getRoomID() << endl;
	cout << "Press 2 to move to room " << room[currentRoom].getRoom2().getRoomID() << endl;
	cout << "Press 3 to move to room " << room[currentRoom].getRoom3().getRoomID() << endl;

	cin >> move;

	switch (move)
	{
		//tung helped
	case 1: currentRoom = room[room[currentRoom].getRoom1().getRoomID() - 1].getRoomID() - 1; break;
	case 2: currentRoom = room[room[currentRoom].getRoom2().getRoomID() - 1].getRoomID() - 1; break;
	case 3: currentRoom = room[room[currentRoom].getRoom3().getRoomID() - 1].getRoomID() - 1; break;
	default: break;
	}
}
