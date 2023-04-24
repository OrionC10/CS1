//functions definitions for maze game
//lab8_Game
//Matthew Crosby
//3/19/2023

#include "Maze.h"


// places every RoomPair to connect two non-existing rooms
// where x-coordinate is -1 and y-coordinate is '*' (a star) to signify
// that the wall is not built yet
void clearWalls(RoomPair walls[]) {
	for (int i = 0; i < numWalls; ++i) {
		walls[i].one.x = -1;
		walls[i].one.y = '*';
		walls[i].two.x = -1;
		walls[i].two.y = '*';
	}
}



// checks if direction dr ('u', 'd', 'l', or 'r')
// applied to Room rm keeps the mouse inside the maze
bool goodDirection(const Room& rm, const char dr) {
	if (dr == 'u' && rm.y - 1 >= 'a') {
		return true;
	}
	if (dr == 'd' && rm.y + 1 <= 'a' + mazeSize - 1) {
		return true;
	}
	if (dr == 'l' && rm.x - 1 >= 1) {
		return true;
	}
	if (dr == 'r' && rm.x + 1 <= mazeSize) {
		return true;
	}
	else {
		return false;
	}
}

// returns the room adjacent to room rm
// in the specified direction dr 
// assumes the direction is inside the maze
Room createAdjacent(const Room& rm, const char dr) {
	if (dr == 'u') {
		Room Tmp;
		Tmp.y = rm.y - 1;
		Tmp.x = rm.x;
		return Tmp;
	}
	if (dr == 'd') {
		Room Tmp;
		Tmp.y = rm.y + 1;
		Tmp.x = rm.x;
		return Tmp;
	}
	if (dr == 'l') {
		Room Tmp;
		Tmp.y = rm.y;
		Tmp.x = rm.x - 1;
		return Tmp;
	}
	if (dr == 'r') {
		Room Tmp;
		Tmp.y = rm.y;
		Tmp.x = rm.x + 1;
		return Tmp;
	}
}



// selects a random room adjacent to Room rm
// uses goodDirection() and createAdjacent()
const Room pickAdjacent(const Room& rm) {
	bool Retry = true;
	while (Retry == true) {
		int R = rand() % 4;
		char dr;
		switch (R) {
		case 0:
			dr = 'u';
			if (goodDirection(rm, dr)) {
				return createAdjacent(rm, dr);
				Retry = false;
			}
			break;
		case 1:
			dr = 'd';
			if (goodDirection(rm, dr)) {
				return createAdjacent(rm, dr);
				Retry = false;
			}
			break;
		case 2:
			dr = 'l';
			if (goodDirection(rm, dr)) {
				return createAdjacent(rm, dr);
				Retry = false;
			}
			break;
		case 3:
			dr = 'r';
			if (goodDirection(rm, dr)) {
				return createAdjacent(rm, dr);
				Retry = false;
			}
		}
	}
}


// selects a random pair, uses pickAdjacent()
const RoomPair pickPair() {
	Room rm;
	int Rx = rand() % mazeSize + 1;
	char Ry = 'a' + rand() % mazeSize;

	rm.x = Rx; rm.y = Ry;

	Room Ajrm = pickAdjacent(rm);
	RoomPair Pair;
	Pair.one.x = rm.x;
	Pair.one.y = rm.y;
	Pair.two.x = Ajrm.x;
	Pair.two.y = Ajrm.y;
	return Pair;
}


// predicate returns true if the coordinates of the two rooms match

bool matchRoom(const Room& Rm1, const Room& Rm2) {
	if (Rm1.x == Rm2.x && Rm1.y == Rm2.y) {
		return true;
	}
	else {
		return false;
	}
}

// returns true if two pairs of adjacent rooms are the same, 
// returns false otherwise, uses matchRoom()

bool matchPair(const RoomPair& Rp1, const RoomPair& Rp2) {
	if (matchRoom(Rp1.one, Rp2.one) && matchRoom(Rp1.two, Rp2.two)
		|| matchRoom(Rp1.two, Rp2.one) && matchRoom(Rp1.one, Rp2.two)) {
		return true;
	}
	else { return false; }
}

// returns true if rp matches one of the wall in the array
// false otherwise
// uses matchPair()
bool checkMaze(const RoomPair Walls[], const RoomPair& rp) {
	bool HitWall;
	for (int i = 0; i < numWalls; ++i) {
		if (matchPair(Walls[i], rp)) {
			return true;
		}
		else { HitWall = false; }
	}
	return HitWall;
}


// places internal walls in random locations of the maze
void build(RoomPair walls[]) {
	for (int i = 0; i < numWalls; ++i) {
		bool Retry = true;
		while (Retry) {
			RoomPair TmpWall = pickPair();
			if (!checkMaze(walls, TmpWall)) {
				walls[i].one.x = TmpWall.one.x;
				walls[i].one.y = TmpWall.one.y;
				walls[i].two.x = TmpWall.two.x;
				walls[i].two.y = TmpWall.two.y;
				Retry = false;
			}
		}
	}
}

//
// display functions
//
#include <iostream> 
using std::cout; using std::endl;

void printRoom(const Room& rm) { // prints the location of the room
	cout << rm.x << rm.y;
}
void printPair(const RoomPair& rp) { // prints the locations of the adjacent rooms
	cout << rp.one.x << rp.one.y << '|' << rp.two.x << rp.two.y << ' ';
}
// prints the locations of all the internal walls of the maze uses printPair
void printMaze(const RoomPair Walls[]) {
	cout << "Walls at ";
	for (int i = 0; i < numWalls; ++i) {
		printPair(Walls[i]);
	}
	cout << endl;
}

//
// game functions
//


using std::cin;
// asks the user for the direction and generates the next room

const Room nextMove(const Room& CurrentRoom) {
	char UserDr;
	cout << 8;
	cin >> UserDr;

	Room NextRoom;
	if (UserDr == 'q') {
		return NextRoom = { -1,'*' };
	}
	else if (goodDirection(CurrentRoom,UserDr)){
		return createAdjacent(CurrentRoom, UserDr);
	}
	else {
		cout << "Wall" << endl;
		return CurrentRoom;
	}
}

// note that checkMaze() is also used in the game