/*Author: Jill Russell
CIS 221 - Project 02
Sort Time Analysis
--Stop Watch Specification File
*/

#ifndef __STOPWATCH__
#define __STOPWATCH__

#pragma warning (disable:6031)
#include <iostream>
#include <time.h>
using namespace std;

class StopWatch {
private:
	clock_t beginTime;
	clock_t endTime;
	clock_t elapsedTime;
	long int secondsElapsed;
	long int milsElapsed;


public:
	StopWatch();
	
	bool Start();
	bool Stop();
	bool IsTicking();
	int MilsElapsed();
};
#endif