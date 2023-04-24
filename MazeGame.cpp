//this calls the maze functions to create the maze game
//Lab8_Game
//Matthew Crosby
//3/19/2023


#include "Maze.h"
#include <iostream>

using std::cout; 
using std::endl;
using std::cin;

int main() {


	//initializing the walls
	srand(time(nullptr));
	RoomPair Walls[numWalls];
	clearWalls(Walls);
	build(Walls);

	//ask user if they want to see the maze walls. print if yes
	char SeeWalls;
	cout << "Would you like to see the maze walls? y/n" << endl;
	cin >> SeeWalls;
	if (SeeWalls == 'y') {
		printMaze(Walls);
	}

	Room Mouse;
	Mouse.x = startRoom.x; Mouse.y = startRoom.y;
	Room QuitRoom = { -1,'*' };
	
	//Game loop
	//while mouse room and cheese room are not =
	//or mouse room not -1,'*'
	while (!matchRoom(Mouse, cheeseRoom)
		&& !matchRoom(Mouse, QuitRoom)) {

		//prints mouse location
		cout << "Current mouse location is: ";
		printRoom(Mouse);
		cout << endl;

		RoomPair UserMove;
		UserMove.one = Mouse; UserMove.two = nextMove(Mouse);

		if (matchRoom(UserMove.two, QuitRoom)) {
			cout << "Exiting Game...";
			Mouse.x = -1; Mouse.y = '*';
		}
		else if (!checkMaze(Walls, UserMove)) {
			Mouse.x = UserMove.two.x; Mouse.y = UserMove.two.y;
		}
		else {
			cout << "Wall" << endl;
		}
		//If UserDr = q, quit game, if UserDr good and no walls move mouse,
		//else hit wall.

		//celebration
		
	}
	if (matchRoom(Mouse, cheeseRoom)) {
			cout << "Congratulations, you found the cheese!!!!!" << endl;
		}
	cout << "Game Over...";
}