#pragma once
#include "string.h"

namespace game
{
	class player
	{
	private:
		char *player_name;
		int player_input;
		int arrow_count;
		bool shootArrow;
		int currentRoom;
	public:
		player(void);
		void update();
		int getRoom();
		int getArrowCount();
		void movement();
		stg::string getName();
		stg::string setName();
	};

	class Room
	{
	private:
		Room *adjacentRooms[3];
		bool isWumpus;
		bool isTrap;
		bool isBat;
		bool isStartingRoom;
		int RoomID;
	public:
		Room(void);
		void setAdjacentRooms(int room1, int room2, int room3, int newRoomID);
		void setRoomHazards(bool wumpus, bool trap, bool bat);
		int getRoomID();
		Room getRoom1();
		Room getRoom2();
		Room getRoom3();
	};

	class Wumpus
	{

	};

	extern Room room[20];

	enum STATE { SPLASH, MAIN, PLAY, GAME, ABOUT, WIN, LOSE, EXIT };

	STATE MainMenu(); // STATE function so it returns which state to go to
					  // Advances the switch statement in Main.cpp

	int getInput(int min, int max); // gets player input for the menu

	void Splash();

	void Exit();

	void Win();

	void Lose();

	void About();

	void CreateMap();

	int Randint(int Min, int Max);
}