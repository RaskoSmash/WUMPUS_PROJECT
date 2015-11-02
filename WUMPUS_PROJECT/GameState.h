#pragma once
#include "string.h"

namespace game
{
	class Wumpus;
	class Cave;
	enum STATE { SPLASH, MAIN, PLAY, GAME, ABOUT, EXIT };

	class player
	{
	private:
		char *player_name;
		size_t playerName;
		int arrow_count;
	//	bool isShootArrow;
		int currentRoom;
		int oldRoom;
		int currentTurn;
		int roomOne;
		int roomTwo;
		int roomThree;

		bool Won;
		//Cave* room;
	public:
		player(void);
	//	player(Cave rooms[]);
		int getRoom();
		
		STATE update(Cave rooms[], Wumpus wumpus1);
	//	int getRoomID();
		int getArrowCount();
		void shootArrow(Cave room[]);
		void movement(Cave rooms[]);
		bool checkWin(Cave room[]);

		/*stg::string getName();
		void setName(const char* a);*/
	};

	class Cave
	{
	private:
		Cave *adjacentRooms[3];
		bool isWumpus;
		bool isTrap;
		bool isBat;
		bool isStartingRoom;
		bool isArrow;
		int RoomID;
	public:
		Cave(void);
		void setAdjacentRooms(Cave room[], int room1, int room2, int room3, int newRoomID);
		void setRoomHazards(bool wumpus, bool trap, bool bat);
		int getRoomID();
		bool getIsWumpus();
		bool getIsBat();
		bool getIsTrap();
		bool getIsArrow();
		
		void setArrow(bool shoot);
		void setWumpus(bool change);

		Cave getRoom1(Cave room[]);
		Cave getRoom2(Cave room[]);
		Cave getRoom3(Cave room[]);
	};

	class Wumpus
	{
	private:
		int prevRoom;
		int curRoom;

		int adjRoom1;
		int adjRoom2;
		int adjRoom3;

	public:
		Wumpus(void);
		int getOldRoom();
		int getNewRoom();
		void setFirstRoom(Cave room[], int i);
		void setNewRoom(Cave room[]);
		
	};

	STATE MainMenu(); // STATE function so it returns which state to go to
					  // Advances the switch statement in Main.cpp

	int getInput(int min, int max); // gets player input for the menu

	void Splash();

	//void Win();

	STATE Exit();

	//void Lose();

	//void About();

	void CreateMap(Cave room[], Wumpus wumpus1);

	int Randint(int min, int max);
}
