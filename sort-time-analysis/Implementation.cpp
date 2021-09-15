/*Author: Jill Russell
CIS 221 - Project 02
Sort Time Analysis
--Implementation File
*/

#include "StopWatch.h"
#include "DataHousing.h"


//STOP WATCH
//constructor
StopWatch::StopWatch() {
	this->beginTime = 0;
	this->endTime = 0;
	this->elapsedTime = 0;
	this->secondsElapsed = 0;
	this->milsElapsed = 0;
}

bool StopWatch::Start() {
	this->beginTime = clock();
	return true;
}

bool StopWatch::Stop() {
	this->endTime = clock();
	return true;
}

//determines if stopwatch is still running
bool StopWatch::IsTicking() {
	if (Start() == true && Stop() == false) {
		return true;
	}
	else if (Start() == true && Stop() == true) {
		return false;
	}
	else {
		return false;
	}
}

//calculates time elapsed - used for individual timers in data
int StopWatch::MilsElapsed() {
	elapsedTime = endTime - beginTime;
	secondsElapsed = elapsedTime / CLOCKS_PER_SEC;					//unused at this point
	return milsElapsed = elapsedTime / (CLOCKS_PER_SEC / 1000);

}



//DATA
//constructor
Data::Data() {
	fileArray = new(int [ARRAY_SIZE]);

	for (int i = 0; i < ARRAY_SIZE; i++) {
		fileArray[i] = 0;
	}
}

Data::Data(string fileName, int arraySize) {
	this->fileName = fileName;
	this->arraySize = arraySize;
	fileArray = new(int [arraySize]);

	for (int i = 0; i < arraySize; i++) {
		fileArray[i] = 0;
	}
}

//deconstructor
Data::~Data() {
	delete[] fileArray;

	fileArray = NULL;
}

//setters
void Data::InitializeArray() {
	int i = 0;
	
	fileArray = new(int[arraySize]);

	for (int i = 0; i < arraySize; i++) {
		fileArray[i] = 0;
	}

	ifstream inputHandle(fileName, ios::in);

	// check for opened file
	if (inputHandle.is_open() == true) {
		// if the file opened, read until end of file is found
		i = 0;
		while (!inputHandle.eof()) {
			if (i < arraySize) {
				inputHandle >> fileArray[i];
				i++;
			}
			else {
				cout << "ERROR: There are too many items in the file. (ARRAY_SIZE = " << arraySize << ")" << endl;
				break;
			}
		}
		cout << "Populating Arrays... <" << arraySize << " elements>" << endl;
		// close the file
		inputHandle.close();
	}
	else {
		// error if file can't be found/opened
		cout << "ERROR: The file \"" << fileName << "\" could not be opened for reading..." << endl;
	}
}

//reset array so it can be sorted again, data only needs to be rewritten at this point
void Data::ResetArray() {
	int i = 0;

	ifstream inputHandle(fileName, ios::in);

	// check to make sure the file opened...
	if (inputHandle.is_open() == true) {
		// if the file opened, read integers until EOF (end of file) is encountered
		i = 0;
		while (!inputHandle.eof()) {
			if (i < arraySize) {
				inputHandle >> fileArray[i];
				i++;
			}
			else {
				cout << "ERROR: There are too many items in the file. (ARRAY_SIZE = " << arraySize << ")" << endl;
				break;
			}
		}

		// close the file now that we are done reading
		inputHandle.close();
	}
	else {
		// if the file didn't open, echo this to the user
		cout << "ERROR: The file \"" << fileName << "\" could not be opened for reading..." << endl;
	}
}

//sorting process!
void Data::SortArray() {
	//attach separate watch elements so they can calculate as we go
	StopWatch bubble;
	StopWatch insert;
	StopWatch select;

	cout << "Sorting..." << endl;
	// timer starts just before bubble sort process, ends just after
	bubble.Start();
	BubbleSort();
	bubble.Stop();

	//reset array to unsorted values, repeat for insertion sort
	ResetArray();
	insert.Start();
	InsertionSort();
	insert.Stop();

	//one last time for selection sort
	ResetArray();
	select.Start();
	SelectionSort();
	select.Stop();

	cout << "SORTS COMPLETE!" << endl;
	//display results using results from each timer
	cout << "Elapsed Time <Bubble Sort>    : " << bubble.MilsElapsed() << " milliseconds" << endl;
	cout << "Elapsed Time <Insertion Sort> : " << insert.MilsElapsed() << " milliseconds" << endl;
	cout << "Elapsed Time <Selection Sort> : " << select.MilsElapsed() << " milliseconds" << endl << endl;

}

void Data::BubbleSort() {
	bool swap = true;
	while (swap == true) {
		swap = false;
		for (int i = 0; i <= arraySize - 2; i++) {
			int j = i + 1;
			if (fileArray[i] > fileArray[j]) {
				int temp = fileArray[j];
				fileArray[j] = fileArray[i];
				fileArray[i] = temp;
				swap = true;
			}
		}
	}
}

void Data::SelectionSort() {
	for (int i = 0; i < arraySize - 1; i++) {
		int currentMin = i;
		for (int j = i + 1; j < arraySize; j++) {
			if (fileArray[j] < fileArray[currentMin])
				currentMin = j;
		}

		int tempNum = fileArray[i];
		fileArray[i] = fileArray[currentMin];
		fileArray[currentMin] = tempNum;
	}
}

void Data::InsertionSort() {
	int currentValue;
	for (int i = 1; i < arraySize; i++) {
		int j = i - 1;
		currentValue = fileArray[i];
		while (fileArray[j] > currentValue && j >= 0) {
			fileArray[j + 1] = fileArray[j];
			j--;
		}
		fileArray[j + 1] = currentValue;
	}
}

//used for testing - displays entire array
void Data::DisplayArray() {
	cout << setiosflags(ios::left);
	for (int i = 0; i < arraySize; i++) {
		cout << setw(6) << fileArray[i];
	}
	cout << endl;
}
