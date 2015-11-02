#include "GameState.h"
#include <iostream>
#include "string.h"
#include <random>
#include <ctime>
#include <cstdlib>
#include "sfwdraw.h"

using namespace std;
//extern game::Cave room[20];
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

game::STATE game::Exit()
{
	int choice = -1;
	cout << "You have left the game." << endl;
	cout << "Do you want to restart?" << endl << "1 for yes, 0 for no: ";
	cin >> choice;

	switch (choice)
	{
	case 0:
		return EXIT; break;
	case 1:
		return MAIN; break;
	default:
		return Exit();
	}
	startOnce = true;
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
	//	startOnce = true;
		return GAME;
	case 2:
		return EXIT;
	case 3:
		return ABOUT;
	case 4:
		return SPLASH;
	default:
		return MAIN;
	}
}

game::Cave::Cave(void): isWumpus(false), isTrap(false), isBat(false), isStartingRoom(false), isArrow(false)
{}

void game::Cave::setAdjacentRooms(Cave room[],int room1, int room2, int room3, int newRoomID)
{
	RoomID = newRoomID;
	adjacentRooms[0] = &room[room1 - 1];
	adjacentRooms[1] = &room[room2 - 1];
	adjacentRooms[2] = &room[room3 - 1];
}



//Cave game::Cave::getRoomID(Cave room[], player player1)
//{
//
//	return room[player1.getRoom()];

//}
bool game::Cave::getIsWumpus()
{
	return isWumpus;
}

bool game::Cave::getIsBat()
{
	return isBat;
}

bool game::Cave::getIsTrap()
{
	return isTrap;
}

bool game::Cave::getIsArrow()
{
	return isArrow;
}

void game::Cave::setArrow(bool shoot)
{
	isArrow = shoot;
}

void game::Cave::setWumpus(bool change)
{
	isWumpus = change;
}

game::Cave game::Cave::getRoom1(Cave room[])
{
	return room[adjacentRooms[0]->getRoomID() - 1];

}
game::Cave game::Cave::getRoom2(Cave room[])
{
	return room[adjacentRooms[1]->getRoomID() - 1];
}

game::Cave game::Cave::getRoom3(Cave room[])
{
	return room[adjacentRooms[2]->getRoomID() - 1];
}

