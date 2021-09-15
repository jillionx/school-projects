/*Author: Jill Russell
CIS 221 - Project 01
Object-Oriented Sliding Tile Puzzle
--Driver File
*/

//Includes, etc
#pragma warning (disable:6031)
#pragma warning (disable:4996)
#include "Specification.h"
using namespace std;

void cls(HANDLE);

int main() {
	//instantiate the class
	SlidingPuzzle someBoard;
	//stuff goes here
	char keyStroke = ' ';						// holds the user's keystrokes as they come in
	int directionCode = UNSET;					// used to build a direction code to be sent to slideTile()
	int gameType = UNSET;
	
	// Seed the Pseudo-Random Number Generator (system clock)
	srand((unsigned int)time(NULL));

	// User sets up board!
	cout << "Choose a puzzle size!" << endl << "1. Default (3x3)"
		<< endl << "2. Custom (best played on boards with 100 values or less)"		// beyond 100 works and even looked fine when expanding each tile for more characters, but display is incredibly hard to play with 3+ digits :(
		<< endl << ": ";
	cin >> gameType;


	while (cin.fail() == true || gameType < DEFAULT || gameType > CUSTOM) {
		cout << "'" << gameType << "' is not a valid selection. Please try again..." << endl;
		cin.clear();
		rewind(stdin);
		gameType = UNSET;
		cin >> gameType;
	}
	if (gameType == DEFAULT) {
		someBoard.InitializeBoard();
		cout << "Default mode selected" << endl;
	}
	else if (gameType == CUSTOM) {
		cout << "How many rows (at least 2): ";
		cin >> someBoard.height;
		while (cin.fail() == true || (someBoard.height < MIN_SIZE)) {
			cout << "'" << someBoard.height << "' is not a valid selection. Please try again..." << endl;
			cin.clear();
			rewind(stdin);
			someBoard.height = UNSET;
			cout << "How many rows (at least 2): ";
			cin >> someBoard.height;
		}
		cout << "How many columns (at least 2): ";
		cin >> someBoard.width;
		while (cin.fail() == true || (someBoard.width < MIN_SIZE)) {
			cout << "'" << someBoard.width << "' is not a valid selection. Please try again..." << endl;
			cin.clear();
			rewind(stdin);
			someBoard.width = UNSET;
			cout << "How many columns (at least 2): ";
			cin >> someBoard.width;
		}
		someBoard.InitializeBoard();
	}
	//Display initial board and prompt for scrambling
	someBoard.PrintBoard();
	cout << "isBoardSolved(): " << boolalpha << someBoard.isBoardSolved() << endl;
	cout << "Press any key to begin.." << endl;
	_getch();
	cout << endl << "Scrambling the tiles..." << endl;
	someBoard.scrambleBoard();
	//verify that scrambling didn't somehow result in a solved board
	someBoard.isBoardSolved();
	while (someBoard.isSolved == true) {
		someBoard.scrambleBoard();
		//reverify
		someBoard.isBoardSolved();
	}
	cout << "Scrambling complete, press any key to begin solving." << endl;
	_getch();
	//clear screen to redraw the scrambled board
	HANDLE currentConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	cls(currentConsoleHandle);


	someBoard.PrintBoard();
	cout << "isBoardSolved(): " << boolalpha << someBoard.isBoardSolved() << endl;
	cout << endl;
	cout << "(W -> UP  |  A -> LEFT |  S -> DOWN  |  D -> RIGHT)" << endl
		<< "Which Way To Slide: ";

	//process keystroke and loop until solved
	while (someBoard.isSolved == false) {
		char keyStroke = getch();
		if (keyStroke == 'w') {
			directionCode = SLIDE_UP;
		}
		else if (keyStroke == 'a') {
			directionCode = SLIDE_LEFT;
		}
		else if (keyStroke == 's') {
			directionCode = SLIDE_DOWN;
		}
		else if (keyStroke == 'd') {
			directionCode = SLIDE_RIGHT;
		}
		else {
			directionCode = UNSET;
			cout << "'" << keyStroke << "' is not a valid selection. Please try again..." << endl;
			cin.clear();
			rewind(stdin);
			keyStroke = ' ';
			_getch();
		}

		someBoard.slidePuzzle(directionCode);

		//clear screen and redisplay after input
		cls(currentConsoleHandle);
		someBoard.PrintBoard();
		directionCode = UNSET;
		cout << "isBoardSolved(): " << boolalpha << someBoard.isBoardSolved() << endl;
		cout << endl;
		cout << "(W -> UP  |  A -> LEFT |  S -> DOWN  |  D -> RIGHT)" << endl
			<< "Which Way To Slide: ";
	}
	
	// Solved state and exit
	cout << endl << "You win! Press any key to exit";
	_getch();
	cls(currentConsoleHandle);
	someBoard.~SlidingPuzzle();
	return 0;

}

void cls(HANDLE hConsole) {
	COORD coordScreen = { 0, 0 };
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;


	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR)' ',
		dwConSize, coordScreen, &cCharsWritten);

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);

	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten);

	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
}