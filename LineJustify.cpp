//take input string and form it into a string that is 80 characters long by inserting spaces to make it long enough
//Lab7_LineJustify
//Matthew Crosby
//3/6/2023

#include "linejustify.h"


int main() {

	//gets users input
	cout << "Enter a string to be justified: " << endl;
	string UserStr;
	getline(cin, UserStr);

	//checks if string is paragraph end
	if (UserStr.size() < MinSize) {
		cout << "Your string is below 40 characters and is justified: ";
		cout << UserStr;
	}
	else {
		PuncSpace(UserStr); //calls first func
		if (UserStr.size() < MaxSize) {
			SpaceAtRand(UserStr); // calls 2nd func
		}

		cout << "This is your line justified sentence with size: " << UserStr.size();
		cout << endl << UserStr;
	}
}