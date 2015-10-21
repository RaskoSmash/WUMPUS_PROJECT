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
Room room[20];

//menu based on the example
int main()
{
	player player1;
	STATE gamestate = PLAY;
	//srand(time(NULL));

	while (true)
	{
		//game::Splash();
		switch (gamestate)
		{
		case SPLASH: Splash();
		case MAIN: gamestate = MainMenu(); break;
		case GAME: CreateMap();
		case PLAY: player1.update(); break;
		case EXIT: return 0;
		}
	}

	system("pause");
}

