#include "GameState.h"
#include <iostream>
#include "string.h"
#include <random>
#include <ctime>
#include <cstdlib>
#include "sfwdraw.h"

extern bool startOnce;
//extern bool isOccupied;
//extern Cave room[20];

void game::CreateMap(Cave room[], Wumpus wumpus1)
{
	
	if (startOnce == true)
	{
		room[0].setAdjacentRooms(room, 6, 2, 5, 1);
		room[1].setAdjacentRooms(room, 7, 1, 3, 2);
		room[2].setAdjacentRooms(room, 8, 2, 4, 3);
		room[3].setAdjacentRooms(room, 9, 3, 5, 4);
		room[4].setAdjacentRooms(room, 10, 4, 1, 5);
		room[5].setAdjacentRooms(room, 11, 1, 15, 6);
		room[6].setAdjacentRooms(room, 12, 2, 11, 7);
		room[7].setAdjacentRooms(room, 13, 3, 12, 8);
		room[8].setAdjacentRooms(room, 14, 4, 13, 9);
		room[9].setAdjacentRooms(room, 15, 5, 14, 10);
		room[10].setAdjacentRooms(room, 16, 6, 7, 11);
		room[11].setAdjacentRooms(room, 17, 7, 8, 12);
		room[12].setAdjacentRooms(room, 18, 8, 9, 13);
		room[13].setAdjacentRooms(room, 19, 9, 10, 14);
		room[14].setAdjacentRooms(room, 20, 10, 6, 15);
		room[15].setAdjacentRooms(room, 20, 11, 17, 16);
		room[16].setAdjacentRooms(room, 18, 12, 16, 17);
		room[17].setAdjacentRooms(room, 19, 13, 17, 18);
		room[18].setAdjacentRooms(room, 20, 14, 18, 19);
		room[19].setAdjacentRooms(room, 16, 15, 19, 20);

		//int RoomsAlreadyUsed[20];

		int randSelection = Randint(1,4);
		if (randSelection == 1)
		{
			room[2].setRoomHazards(false, false, true);
			room[5].setRoomHazards(false, false, false);
			room[8].setRoomHazards(false, true, false);
			room[12].setRoomHazards(true, false, true);
			room[15].setRoomHazards(false, true, false);
		}
		else if (randSelection == 2)
		{
			room[4].setRoomHazards(true, false, false);
			room[0].setRoomHazards(false, true, false);
			room[13].setRoomHazards(false, true, false);
			room[17].setRoomHazards(false, false, true);
			room[9].setRoomHazards(false, false, true);
		}
		else if (randSelection == 3)
		{
			room[3].setRoomHazards(false, false, true);
			room[6].setRoomHazards(false, false, false); 
			room[11].setRoomHazards(false, true, false);
			room[1].setRoomHazards(true, false, true);
			room[14].setRoomHazards(false, true, false);
		}
		else if (randSelection == 4)
		{
			room[16].setRoomHazards(false, false, true);
			room[18].setRoomHazards(false, false, false);
			room[7].setRoomHazards(false, true, false);
			room[19].setRoomHazards(true, false, true);
			room[10].setRoomHazards(false, true, false);
		}

		for (int i = 0; i < 20; ++i)
		{
			if (room[i].getIsWumpus())
			{
				wumpus1.setFirstRoom(room, i);
				break;
			}
		}


		startOnce = false;
	}

}

//help from tung
int game::Randint(int min, int max)
{
	return min + (rand() % (max - min + 1));
	//return rand() % max + min;
}

void game::Cave::setRoomHazards(bool wumpus, bool trap, bool bat)
{
	isWumpus = wumpus;
	isTrap = trap;
	isBat = bat;
}

int game::Cave::getRoomID()
{
	return RoomID;
}

