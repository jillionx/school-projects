/*Author: Jill Russell
CIS 221 - Project 02
Sort Time Analysis
--Driver File
*/

#include "StopWatch.h"
#include "DataHousing.h"

int main() {
	//declaring stuff to be sorted!
	Data file500(FILE_500, SIZE_500);
	Data file5K(FILE_5K, SIZE_5K);
	Data file25K(FILE_25K, SIZE_25K);
	Data file100K(FILE_100K, SIZE_100K);

	//sort the stuff!
	//sort for 500
	file500.InitializeArray();
	file500.SortArray();

	//sort for 5K
	file5K.InitializeArray();
	file5K.SortArray();

	//sort for 25K
	file25K.InitializeArray();
	file25K.SortArray();

	//sort for 100K
	file100K.InitializeArray();
	file100K.SortArray();

	// display completion and exit program
	cout << "ANALYSIS COMPLETE... PRESS ANY KEY TO CONTINUE";
	_getch();
	file500.~Data();
	file5K.~Data();
	file25K.~Data();
	file100K.~Data();
	return 0;
}
