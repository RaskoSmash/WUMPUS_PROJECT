#include "GameState.h"
#include <iostream>
#include "string.h"
#include <random>
#include <ctime>
#include <cstdlib>
#include "sfwdraw.h"

using namespace std;

extern bool startOnce;

int game::getInput(int min, int max)
{
	int option = -1;

	do 
	{
		cout << "Please enter a number between " << min << " and " << max << endl;
		cin >> option;

		if (cin.fail() || option > max || option < min)
		{
			std::cin.clear();
			std::cin.ignore(80, '\n');
			system("cls");
			std::cout << "Please enter a valid number." << std::endl;

		}
		else break;
	} while (true);
	return option;
}

void game::Splash()
{
	system("cls");
//	float timer = sfw::getDeltaTime() / 2;
	cout << "Welcome to Hunt the Wumpus!" << endl;
	cout << "Pressing any key will proceed you to the Main Menu." << endl;
//	cout << sfw::getDeltaTime() << endl;
//	while (true)
//	{
//		if (timer > .1)
//		{
//			break;
//		}
//	}
	system("pause");
}

game::STATE game::MainMenu()
{
	system("cls");
	cout << "This is the Main Menu, the following numbers will..." << endl;
	cout << "1: Start game" << endl;
	cout << "2: Exit the game" << endl;
	cout << "3: Go to the about/credits screen" << endl;
	cout << "4: Go to the Splash screen" << endl;

	switch (game::getInput(1,4))
	{
	case 1:
		return PLAY;
	case 2:
		return EXIT;
	case 3:
		return ABOUT;
	case 4:
		return SPLASH;
	}
}

game::Room::Room(void)
{
	isWumpus = false;
	isTrap = false;
	isBat = false;
	isStartingRoom = false;
}

void game::Room::setAdjacentRooms(int room1, int room2, int room3, int newRoomID)
{
	RoomID = newRoomID;
	adjacentRooms[0] = &room[room1 - 1];
	adjacentRooms[1] = &room[room2 - 1];
	adjacentRooms[2] = &room[room3 - 1];
}



int game::Room::getRoomID()
{
	return RoomID;
}

game::Room game::Room::getRoom1()
{
	return room[adjacentRooms[0]->getRoomID() -1];
}

game::Room game::Room::getRoom2()
{
	return room[adjacentRooms[1]->getRoomID() - 1];
}

game::Room game::Room::getRoom3()
{
	return room[adjacentRooms[2]->getRoomID() - 1];
}


