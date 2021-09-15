/*Author: Jill Russell
CIS 221 - Project 3
Operator Overloaded Linked List
--Driver File
*/

//disable getch warning
#pragma warning (disable:6031)

//Includes
#include <iostream>
#include <iomanip>
using namespace std;
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Specification.h"

//Constants
const int lowerElements = 100;				//lowest number of elements to add
const int upperElements = 100000;			//highest number of elements to add
const int lowerAdd = 1;						//lowest integer to add to list
const int upperAdd = 100;					//highest integer to add to list
const int firstDeletion = 50;				//first round of deletions goes up to 50
const int secondDeletion = 100;				//second round of deletions completes through 100
const int maxLoops = 100;					//number of cycles the program will run

int randInterval(int, int);

int main() {
	//RNG seed
	srand((unsigned int)time(NULL));

	//instantiate the list
	OOLList theList;

	//will loop through 100 cycles
	for (int i = 1; i <= maxLoops; i++) {
		cout << "Cycle #" << i << endl;
		//step 1 - show contents when empty
		theList.getListSize();
		//step 2 - add random values to list
		int elementCount = randInterval(lowerElements, upperElements);
		for (int i = 0; i < elementCount; i++) {
			theList.addElement(randInterval(lowerAdd, upperAdd));
		}

		//step 3 - reseed for a new amount of elements, uses operator overloaded add
		elementCount = randInterval(lowerElements, upperElements);
		for (int i = 0; i < elementCount; i++) {
			theList + randInterval(lowerAdd, upperAdd);
		}
		//display size of list for fun
		theList.getListSize();

		//step 4 - delete 1-50
		for (int i = 0; i <= firstDeletion; i++) {
			while (theList.deleteElement(i) == true);
		}

		//step 5 - start from end of last step and delete up to 100
		for (int i = firstDeletion; i <= secondDeletion; i++) {
			while (theList - i == true);
		}
		//displays an empty list again!
		theList.getListSize();
	}

	_getch();
	return 0;
}

//sets random numbers
int randInterval(int lower, int upper) {
	return lower + (rand() % (upper - lower + 1));
}