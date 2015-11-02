#include "GameState.h"
#include <iostream>
#include "string.h"
#include <random>
#include <ctime>
#include <cstdlib>
#include "sfwdraw.h"
#include <fstream>

extern void cheat(game::Cave room[]);

using namespace game;
using namespace std;

game::player::player(void): arrow_count(5), currentTurn(0), roomOne(0), roomTwo(0), roomThree(0), Won(false), currentRoom(Randint(1, 20))
{}

int game::player::getRoom()
{
	return currentRoom;
}

game::STATE game::player::update(Cave room[], Wumpus wumpus1)
{
	system("cls");
	currentTurn++;
	roomOne = room[currentRoom - 1].getRoom1(room).getRoomID();
	roomTwo = room[currentRoom - 1].getRoom2(room).getRoomID();
	roomThree = room[currentRoom - 1].getRoom3(room).getRoomID();

	if (oldRoom != 0)
	{
		cout << "Your last room was: " << oldRoom << endl;
		cout << "Your current room is " << currentRoom << " on turn " << currentTurn << endl;
	}
	else
	{
		cout << "You have just fell into room " << currentRoom << " on turn 1" << endl;
	}
	oldRoom = currentRoom;
	
	cout << "Your arrow count is: " << arrow_count << endl;
	cout << "This room leads to " << roomOne << endl;
	cout << "This room leads to " << roomTwo << endl;
	cout << "This room leads to " << roomThree << endl;

	if (room[roomOne - 1].getIsTrap() || room[roomTwo - 1].getIsTrap() || room[roomThree - 1].getIsTrap())
	{
		cout << endl << "There is a breeze nearby." << endl;
	}
	else if (room[roomOne - 1].getIsWumpus() || room[roomTwo - 1].getIsWumpus() || room[roomThree - 1].getIsWumpus())
	{
		cout << endl << "I smell a foul odor." << endl;
	}

	if (room[currentRoom - 1].getIsBat())
	{
		cout << endl << "A bat picks me up and drops me in a random room." << endl;
		system("pause");
		int oldRoom = currentRoom;
		currentRoom = Randint(1, 20);
		if (oldRoom == currentRoom)
		{
			currentRoom -= 1;
		}
		return PLAY;
	}
	else if (room[currentRoom - 1].getIsTrap())
	{
		cout << "You fell down a pit and died. Game Over" << endl;
		return Exit();
	}
	else if (room[currentRoom - 1].getIsWumpus())
	{
		cout << "You ran into the room with the wumpus!" << endl << "You we're eaten! Game Over" << endl;
		return Exit();
	}
	else
	{
		//cheat(room);

		int choice = 0;
		cout << endl;
		cout << "Input 1 to shoot" << endl;
		cout << "Input 2 to move" << endl;
		cout << "Input 3 to exit" << endl;

		cin >> choice;

		switch (choice)
		{
		case 1: shootArrow(room); break;
		case 2: movement(room); break;
		case 3: Exit(); break;
		default: 
			cout << "Invalid Input: " << endl;
			system("pause");
			system("cls");
			update(room, wumpus1); break;
		}
		if (Won)
		{
			return Exit();
		}
		else
		{
			/*if (arrow_count <= 4)
			{
			wumpus1.setNewRoom(room);
			}*/
			/*else*/if (arrow_count <= 0)
			{
				cout << "You ran out of arrows! Game Over" << endl;
				return Exit();
			}
			else
			{
				return PLAY;
			}
		}
	}
	
}

int game::player::getArrowCount()
{
	return arrow_count;
}

void game::player::shootArrow(Cave room[])
{
	cout << endl;
	int input = 0;
	cout << "Input 1 to shoot to room: " << roomOne << endl;
	cout << "Input 2 to shoot to room: " << roomTwo << endl;
	cout << "Input 3 to shoot to room: " << roomThree << endl;
	cin >> input;
	cout << endl;

	Won = checkWin(room);

	switch (input)
	{
	case 1: room[roomOne - 1].setArrow(true); cout << "You shot the arrow in room " << roomOne << endl; Won; break;
	case 2: room[roomTwo - 1].setArrow(true); cout << "You shot the arrow in room " << roomTwo << endl; Won;  break;
	case 3: room[roomThree - 1].setArrow(true); cout << "You shot the arrow in room " << roomThree << endl; Won;  break;
	default:
		cout << "Invalid Input: " << endl;
		system("pause");
		system("cls");
		shootArrow(room); break;
	}
	arrow_count--;
}

void game::player::movement(Cave room[])
{
	int move = 0;
	cout << "Press 1 to move to room " << roomOne << endl;
	cout << "Press 2 to move to room " << roomTwo << endl;
	cout << "Press 3 to move to room " << roomThree << endl;

	cin >> move;

	switch (move)
	{
		//tung helped
	case 1: currentRoom = roomOne; break;
	case 2: currentRoom = roomTwo; break;
	case 3: currentRoom = roomThree; break;
	default: 
		cout << "Invalid Input: " << endl; 
		system("pause");
		system("cls"); 
		movement(room); break;
	}
}

bool game::player::checkWin(Cave room[])
{
	if (   room[roomOne - 1].getIsArrow()   && room[roomOne - 1].getIsWumpus() 
		|| room[roomTwo - 1].getIsArrow()   && room[roomTwo - 1].getIsWumpus() 
		|| room[roomThree - 1].getIsArrow() && room[roomThree - 1].getIsWumpus())
	{
		fstream file;
		file.open("SaveData.txt", ios_base::out);

		system("cls");
		if (room[roomOne - 1].getIsWumpus())
		{
			cout << "Congratulations you slayed the wumpus in room " << roomOne << " on turn " << currentTurn << endl;
			if (file.is_open())
			{
				file << "Congratulations you slayed the wumpus in room " << roomOne << " on turn " << currentTurn;
			}
		}
		else if (room[roomTwo - 1].getIsWumpus())
		{
			cout << "Congratulations you slayed the wumpus in room " << roomTwo << " on turn " << currentTurn << endl;
			if (file.is_open())
			{
				file << "Congratulations you slayed the wumpus in room " << roomTwo << " on turn " << currentTurn;
			}
		}
		else if (room[roomThree - 1].getIsWumpus())
		{
			cout << "Congratulations you slayed the wumpus in room " << roomThree << " on turn " << currentTurn << endl;
			if (file.is_open())
			{
				file << "Congratulations you slayed the wumpus in room " << roomThree << " on turn " << currentTurn;
			}
		}
		file.close();
		return true;
	}
	else
	{
		cout << "Your arrow clashes with a wall after hitting nothing." << endl << "You woke the wumpus!" << endl;
		system("pause");
		return false;
	}
}

//stg::string game::player::getName()
//{
//	return player_name;
//}
//
//void game::player::setName(const char* a)
//{
//	player_name = a;
//}
