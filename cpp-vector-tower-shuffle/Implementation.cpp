/*Author: Jill Russell
CIS 221 - Assignment 10
STL Vector Tower Shuffle
--Implementation File
*/

#include "Towers.h"

//constructor
Towers::Towers() {
	vector<int> t_0;
	vector<int> t_1;
	vector<int> t_2;

	vector<int> solved_0;
	vector<int> solved_1;
	vector<int> solved_2;
}

void Towers::InitializeTowers() {
	//clear all vectors from previous games, etc
	t_0.clear();
	t_1.clear();
	t_2.clear();
	solved_0.clear();
	solved_1.clear();
	solved_2.clear();

	//adds initial values to each tower
	t_0.push_back(0);
	t_0.push_back(0);
	t_1.push_back(1);
	t_1.push_back(1);
	t_2.push_back(2);
	t_2.push_back(2);

	solved_0.push_back(0);
	solved_0.push_back(0);
	solved_1.push_back(1);
	solved_1.push_back(1);
	solved_2.push_back(2);
	solved_2.push_back(2);
}

void Towers::MoveTowers(int src, int dst) {
	//checks for empty towers, sets to correct tower object otherwise
	//use temp variable to store src tower for transfer
	int temp = UNSET;
	bool success = false;

	if (src == 0) {
		if (t_0.empty() == true) {
			success = false;
		}
		else {
			temp = t_0[t_0.size() - 1];
			t_0.pop_back();
			success = true;
		}
	}
	else if (src == 1) {
		if (t_1.empty() == true) {
			success = false;
		}
		else {
			temp = t_1[t_1.size() - 1];
			t_1.pop_back();
			success = true;
		}
	}
	else if (src == 2) {
		if (t_2.empty() == true) {
			success = false;
		}
		else {
			temp = t_2[t_2.size() - 1];
			t_2.pop_back();
			success = true;
		}
	}
	if (dst == 0 && success == true) {
		t_0.push_back(temp);
	}
	else if (dst == 1 && success == true) {
		t_1.push_back(temp);
	}
	else if (dst == 2 && success == true) {
		t_2.push_back(temp);
	}

}

void Towers::ScrambleTowers() {
	int src = UNSET;
	int dst = UNSET;

	// random values generated with % 3 to return values of 0-2
	for (int i = 0; i < MAX_MOVES; i++) {
		src = rand() % 3;
		dst = rand() % 3;
		MoveTowers(src, dst);
	}
	

}

void Towers::DisplayGame() {
	cout << "Tower 0: ";
	DisplayTower(t_0);
	cout << "Tower 1: ";
	DisplayTower(t_1);
	cout << "Tower 2: ";
	DisplayTower(t_2);
}

void Towers::DisplayTower(vector<int> tower) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//sets red for 0000, green for 0001, and blue for 0002, leaves empty towers white
	if (tower.empty() == true) {
		SetConsoleTextAttribute(hConsole, 15);
		cout << setw(4) << "empty";
	}
	for (int i = 0; i < tower.size(); i++) {
		if (tower[i] == 0) {
			SetConsoleTextAttribute(hConsole, 12);
		}
		else if (tower[i] == 1) {
			SetConsoleTextAttribute(hConsole, 10);
		}
		else if (tower[i] == 2) {
			SetConsoleTextAttribute(hConsole, 11);
		}
		cout << setfill('0') << setw(4) << tower[i] << " ";
		SetConsoleTextAttribute(hConsole, 15);
	}
	cout << endl;

}

bool Towers::IsGameSolved() {
	//checks solved status for game completion and successful scrambling
	if (t_0 == solved_0 && t_1 == solved_1 && t_2 == solved_2) {
		return true;
	}
	else return false;
}