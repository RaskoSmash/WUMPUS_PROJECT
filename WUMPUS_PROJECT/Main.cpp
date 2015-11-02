#include <sstream>
#include <iostream>
#include <climits>
#include <fstream>
#include "string.h"
#include <cassert>
#include <crtdbg.h>
#include "GameState.h"
#include <ctime>

using namespace game;
bool startOnce = true;
//bool isOccupied = false;

void cheat(Cave room[]);

//menu based on the example
int main()
{
	srand(time(NULL));
	Cave room[20];
	player player1;
	Wumpus wumpus1;
	STATE gamestate = GAME;
	//srand(time(NULL));

	while (gamestate != EXIT)
	{
		//game::Splash();
		switch (gamestate)
		{
		case SPLASH: Splash();
		case MAIN: gamestate = MainMenu(); break;
		case GAME: CreateMap(room, wumpus1);
		//case PAUSE: gamestate = Pause(); player1.draw(); break;
		case PLAY: gamestate = player1.update(room, wumpus1); break;
		case EXIT: return 0;
		}
	}

	system("pause");
}

void cheat(Cave room[])
{
	for (int i = 0; i < 20; ++i)
	{
		if (room[i].getIsWumpus())
		{
			std::cout << "Wumpus in room: " << room[i].getRoomID() << std::endl;
		}
		else if (room[i].getIsBat())
		{
			std::cout << "Bat in room: " << room[i].getRoomID() << std::endl;
		}
		else if (room[i].getIsTrap())
		{
			std::cout << "Pit in room: " << room[i].getRoomID() << std::endl;
		}
	}
}