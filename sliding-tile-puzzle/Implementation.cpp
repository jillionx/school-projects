/*Author: Jill Russell
CIS 221 - Project 01
Object-Oriented Sliding Tile Puzzle
--Implementation File
*/

//Include specification file
#include "Specification.h"

//Constructor
SlidingPuzzle::SlidingPuzzle() {
	theBoard = new(int* [DEFAULT_ROWS]);

	for (int i = 0; i < DEFAULT_ROWS; i++) {
		theBoard[i] = new(int[DEFAULT_COLS]);
	}

	int counter = 1;
	for (int i = 0; i < DEFAULT_ROWS; ++i) {
		for (int j = 0; j < DEFAULT_COLS; ++j) {
			theBoard[i][j] = counter++;
		}
	}
	theBoard[DEFAULT_ROWS - 1][DEFAULT_COLS - 1] = PIVOT;
}

SlidingPuzzle::SlidingPuzzle(int width, int height) {
	theBoard = new(int* [height]);

	for (int i = 0; i < height; i++) {
		theBoard[i] = new(int[width]);
	}

	int counter = 1;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			theBoard[i][j] = counter++;
		}
	}
	theBoard[height - 1][width - 1] = PIVOT;
}


//deconstructor method
SlidingPuzzle::~SlidingPuzzle() {
	for (int i = 0; i < height; i++) {
			delete[] theBoard[i];
	}
	delete[] theBoard;

	theBoard = NULL;

	for (int i = 0; i < height; i++) {
			delete[] solvedBoard[i];
		}
	delete[] solvedBoard;

	solvedBoard = NULL;
}

void SlidingPuzzle::InitializeBoard() {
	//for theBoard
	theBoard = new(int* [height]);

	for (int i = 0; i < height; i++) {
		theBoard[i] = new(int[width]);
	}

	int counter = 1;
	while (counter < (height + width)) {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				theBoard[i][j] = counter++;
			}
		}
		theBoard[height - 1][width - 1] = PIVOT;
	}

	//for solvedBoard
	solvedBoard = new(int* [height]);

	for (int i = 0; i < height; i++) {
		solvedBoard[i] = new(int[width]);
	}

	counter = 1;
	while (counter < (height + width)) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				solvedBoard[i][j] = counter++;
			}
		}
		solvedBoard[height - 1][width - 1] = PIVOT;
	}

}

bool SlidingPuzzle::isBoardSolved() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (theBoard[i][j] == solvedBoard[i][j]) {
				isSolved = true;
			}
			else {
				return isSolved = false;
			}
		}
	}
	return isSolved;
}
bool SlidingPuzzle::slidePuzzle(int slideDirection) {
	//if move is possible, it will return true, if the move fails, return false
	int pivotRow = 0;
	int pivotCol = 0;
	int pivotSpace = 0;
	bool moveSuccess = true;
	//find pivot point
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (theBoard[i][j] == PIVOT) {
				pivotRow = i;
				pivotCol = j;
			}
		}
	}
	//check pivot against illegal moves and make move if legal
	switch (slideDirection) {
	case SLIDE_UP:
		if ((pivotRow + 1) >= height) {		//check up move
			moveSuccess = false;
		}
		else {
			theBoard[pivotRow][pivotCol] = theBoard[pivotRow + 1][pivotCol];
			theBoard[pivotRow + 1][pivotCol] = PIVOT;
		}
		break;
	case SLIDE_LEFT:
		if ((pivotCol + 1) >= width) {		//check left
			moveSuccess = false;
			}
		else {
			theBoard[pivotRow][pivotCol] = theBoard[pivotRow][pivotCol + 1];
			theBoard[pivotRow][pivotCol + 1] = PIVOT;
		}
		break;
	case SLIDE_DOWN:
		if ((pivotRow - 1) < 0) {				//check down
			moveSuccess = false;
		}
		else {
			theBoard[pivotRow][pivotCol] = theBoard[pivotRow - 1][pivotCol];
			theBoard[pivotRow - 1][pivotCol] = PIVOT;
		}
		break;
	case SLIDE_RIGHT:
		if ((pivotCol - 1) < 0) {				//check right
			moveSuccess = false;
		}
		else {
			theBoard[pivotRow][pivotCol] = theBoard[pivotRow][pivotCol - 1];
			theBoard[pivotRow][pivotCol - 1] = PIVOT;
		}
		break;
	}
	return moveSuccess;
}
void SlidingPuzzle::scrambleBoard() {
	int randomMove = UNSET;
	int numMoves = UNSET;

	for (int i = 0; i < MAX_MOVES; i++) {
		randomMove = rand() % 5;			// returns 1-4 for move direction
		slidePuzzle(randomMove);
	}
}
void SlidingPuzzle::PrintBoard() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << left;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (theBoard[i][j] == PIVOT) {
				SetConsoleTextAttribute(hConsole, 15);
				cout << setw(3) << PIVOT_SYMBOL;
			}
			// number in correct position
			if (theBoard[i][j] == ((i * width) + (j + 1))) {
				SetConsoleTextAttribute(hConsole, 10);
			}
			else {
				SetConsoleTextAttribute(hConsole, 12);
			}
			if (theBoard[i][j] != PIVOT) {
				cout << setw(3) << theBoard[i][j];
			}
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
}