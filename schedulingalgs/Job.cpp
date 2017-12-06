#include "stdafx.h"
#include "Job.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
void Job::print()
{
	cout << toStr();
}

Job::Job(double arrival, double timeRequired) {
	this->arrival = arrival;
	this->timeRequired = timeRequired;
	this->startTime = (double)NULL;
	this->endTime = (double)NULL;
	this->waitTime = (double)NULL;
	this->turnAround = (double)NULL;
}

string Job::toStr()
{	
	ostringstream os;
	os << "process id: " << procId << endl;
	os << "arrival: " << arrival << endl;
	os << "time required: " << timeRequired << endl;
	os << "start time: " << startTime << endl;
	os << "end time: " << endTime << endl;
	os << "wait time: " << waitTime << endl;
	os << "turn around: " << turnAround << endl;
	return os.str();
}
