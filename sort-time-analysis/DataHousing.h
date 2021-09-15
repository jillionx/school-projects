/*Author: Jill Russell
CIS 221 - Project 02
Sort Time Analysis
--Data Housing Specification File
*/

#ifndef __DATA__
#define __DATA__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
using namespace std;

#define FILE_500		"NumFile500.txt"
#define FILE_5K			"NumFile5K.txt"
#define FILE_25K		"NumFile25K.txt"
#define FILE_100K		"NumFile100K.txt"
#define ARRAY_SIZE		5000
#define SIZE_500		500
#define SIZE_5K			5000
#define SIZE_25K		25000
#define SIZE_100K		100000


class Data {
private:
	int* fileArray = NULL;
	int arraySize = ARRAY_SIZE;
	string fileName;

public:
	//constructors
	Data();
	Data(string, int);

	//deconstructor
	~Data();

	void InitializeArray();
	void ResetArray();
	void SortArray();
	void BubbleSort();
	void SelectionSort();
	void InsertionSort();
	void DisplayArray();


};
#endif
