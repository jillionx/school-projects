/*Author: Jill Russell
CIS 221 - Assignment 10
STL Vector Tower Shuffle
--Driver File
*/

#pragma warning(disable:6031)

#include "Towers.h"

void cls(HANDLE);

int main() {
	//set towers object; set src, dst, and gameOption variables for user input
	int gameOption = UNSET;
	int src = UNSET;
	int dst = UNSET;
	Towers towers;
	HANDLE currentConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Seed the Pseudo-Random Number Generator (system clock)
	srand((unsigned int)time(NULL));

	//initialize and display game
	towers.InitializeTowers();
	towers.DisplayGame();
	while (gameOption != EXIT) {
		//start with game selection
		cout << "1.) New Game" << endl << "2.) Exit Game"
			<< endl << "Please select an option: ";
		cin >> gameOption;
		while (cin.fail() == true || (gameOption != NEW && gameOption != EXIT)) {
			cout << "That is not a valid selection. Please try again" << endl;
			cin.clear();
			rewind(stdin);
			gameOption = UNSET;
			cout << endl << "1.) New Game" << endl << "2.) Exit Game"
				<< endl << "Please select an option: ";
			cin >> gameOption;
		}

		//scramble towers on game start
		if (gameOption == NEW) {
			towers.InitializeTowers();
			cout << "Scrambling...";
			towers.ScrambleTowers();
			while (towers.IsGameSolved() == true) {
				towers.ScrambleTowers();
				//reverify
				towers.IsGameSolved();
			}
			cout << "The towers have been scrambled on " << MAX_MOVES << " moves"
				<< endl << "Press any key to solve!";
			_getch();
		}
		cls(currentConsoleHandle);

		//redisplay and begin
		towers.DisplayGame();
		//begin loop until solved
		while (towers.IsGameSolved() == false) {
			//prompt user for tower to move from
			cout << endl << "Please enter a source tower (0, 1, or 2): ";
			cin >> src;
			while (cin.fail() == true || src < MIN || src > MAX) {
				cout << "That is not a valid selection. Please try again" << endl
					<< "Please enter a source tower (0, 1, or 2): ";
				cin.clear();
				rewind(stdin);
				src = UNSET;
				cin >> src;
			}
			//prompt user for tower to move to
			cout << "Please enter a destination tower (0, 1, or 2): ";
			cin >> dst;
			while (cin.fail() == true || dst < MIN || dst > MAX) {
				cout << "That is not a valid selection. Please try again" << endl
					<< "Please enter a destination tower (0, 1, or 2): ";
				cin.clear();
				rewind(stdin);
				src = UNSET;
				cin >> dst;
			}
			//process move
			towers.MoveTowers(src, dst);

			//clear screen and redisplay for next move
			cls(currentConsoleHandle);
			towers.DisplayGame();
		}
		//display win message when first completed
		if (towers.IsGameSolved() == true && gameOption != EXIT) {
			cout << endl << "You've solved it!" << endl
				<< "Press any key...";
			_getch();
			cls(currentConsoleHandle);
		}
	}
	//clear screen and exit
	cls(currentConsoleHandle);
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