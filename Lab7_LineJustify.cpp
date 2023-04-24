//this holds the functions needed for the line justify in lab 7
//Lab7_LineJustify
//Matthew Crosby
//3/6/2023

#include "linejustify.h"


//find punctuations with white spaces after and add space.
void PuncSpace(string& UserIn) {

	string SearchFor = ".,:?!";
	int Npos = string::npos; // npos is returned when search reaches end of string
	int Pos = UserIn.find_first_of(SearchFor);

	while (UserIn.size() < MaxSize && Pos != Npos && Pos + 1 != UserIn.size()) {

		if (UserIn[Pos + 1] == ' ') {
			UserIn.insert(Pos + 1, 1, ' ');
		}

		Pos = UserIn.find_first_of(SearchFor, Pos + 1);
	}
}


//adds space where there is space until UserIn.size() == MaxSize
//find starts at random part of the string
void SpaceAtRand(string& UserIn) {

	srand(time(nullptr));
	int Pos; int RPos;
	int NPos = string::npos;
	Pos = UserIn.find_first_of(" ");
	if (Pos != NPos) {
		while (UserIn.size() < MaxSize) {
			RPos = rand() % UserIn.size();
			Pos = UserIn.find_first_of(" ", RPos);
			if (Pos != NPos) {
				UserIn.insert(Pos, 1, ' ');
			}
		}
	}
}