/*Author: Jill Russell
CIS 221 - Project 01
Object-Oriented Sliding Tile Puzzle
--Specification File
*/

//Class
#ifndef __PUZZLE__
#define __PUZZLE__

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
using namespace std;

#define DEFAULT_ROWS	3		// rows for default game mode
#define DEFAULT_COLS	3		// cols for default game mode
#define MIN_SIZE		2		// needs at least 2 tiles in each direction to be playable

#define PIVOT			-1		// used to mark the pivot spot (blank area) on the puzzle
#define PIVOT_SYMBOL	"*"		// used to show the pivot location when drawing the board

// direction codes (part of the slideTile() interface)
#define SLIDE_UP		1		// pass to slideTile() to trigger UP movement
#define SLIDE_DOWN		2		// pass to slideTile() to trigger DOWN movement
#define SLIDE_LEFT		3		// pass to slideTile() to trigger LEFT movement
#define SLIDE_RIGHT		4		// pass to slideTile() to trigger RIGHT movement

#define MAX_MOVES		10000	// max number of moves for shuffling

#define UNSET			-1		// to declare unset values

#define DEFAULT			1		// user input to set default game mode of 3x3
#define CUSTOM			2		// user input to set custom game mode

#define COLOR_DEFAULT	7		// colors for PrintBoard();
#define COLOR_RED		12
#define COLOR_GREEN		10


class SlidingPuzzle {
private:
	int** theBoard = NULL;
	int** solvedBoard = NULL;

public:
	int width = DEFAULT_COLS;
	int height = DEFAULT_ROWS;
	bool isSolved = false;


	//constructors
	SlidingPuzzle();
	SlidingPuzzle(int width, int height);


	//deconstructor method
	~SlidingPuzzle();

	void InitializeBoard();
	bool isBoardSolved();
	bool slidePuzzle(int directionCode);
	void scrambleBoard();
	void PrintBoard();
};
#endif