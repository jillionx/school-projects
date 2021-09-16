/*Author: Jill Russell
CIS 221 - Assignment 10
STL Vector Tower Shuffle
--Towers Specification File
*/

#ifndef __TOWERS__
#define __TOWERS__

#include <iostream>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;

#define UNSET		-1		//to declare unset values

#define NEW			1		//game option - start game
#define EXIT		2		//game option - exit

#define MAX_MOVES	50		//max moves for scrambling

#define MIN			0		//min for tower values
#define MAX			2		//max for tower values

class Towers {
private:
	//towers for gameplay
	vector<int> t_0;
	vector<int> t_1;
	vector<int> t_2;
	//unchanged towers for solve checks
	vector<int> solved_0;
	vector<int> solved_1;
	vector<int> solved_2;

public:
	//constructor
	Towers();

	void InitializeTowers();
	void MoveTowers(int, int);
	void ScrambleTowers();
	void DisplayGame();
	void DisplayTower(vector<int>);
	bool IsGameSolved();
};
#endif