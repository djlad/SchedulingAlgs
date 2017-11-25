#pragma once
#include <string>
using namespace std;
class Job {
public:
	int procId;
	double arrival;
	double timeRequired;
	double timeRemaining;
	double startTime;
	double endTime;
	double waitTime;
	double turnAround;

	Job() {};

	Job(double arrival, double timeRequired); 
	string toStr();
	void print();
};

