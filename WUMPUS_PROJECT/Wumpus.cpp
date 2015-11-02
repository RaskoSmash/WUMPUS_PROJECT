#include "GameState.h"
#include <iostream>
#include "string.h"
#include <random>
#include <ctime>
#include <cstdlib>
#include "sfwdraw.h"


game::Wumpus::Wumpus(void) : prevRoom(0), curRoom(0), adjRoom1(0), adjRoom2(0), adjRoom3(0)
{}

int game::Wumpus::getOldRoom()
{
	return prevRoom;
}

int game::Wumpus::getNewRoom()
{
	return curRoom;
}

void game::Wumpus::setFirstRoom(Cave room[], int i)
{
	curRoom = room[i].getRoomID();
}

void game::Wumpus::setNewRoom(Cave room[])
{
	room[curRoom - 1].setWumpus(false);
	int RandChange = Randint(1, 3);

	adjRoom1 = room[curRoom - 1].getRoom1(room).getRoomID();
	adjRoom2 = room[curRoom - 1].getRoom2(room).getRoomID();
	adjRoom3 = room[curRoom - 1].getRoom3(room).getRoomID();

	switch (RandChange)
	{
	case 1: curRoom = adjRoom1;
	case 2: curRoom = adjRoom2;
	case 3: curRoom = adjRoom3;
	}
	room[curRoom - 1].setWumpus(true);
}
