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
	this->startTime = -1;//-1 means unset
	this->endTime = -1;
	this->waitTime = -1;
	this->turnAround = -1;
}

string Job::toStr()
{	
	ostringstream os;
	os << "Process id: " << procId << endl;
	os << "arrival: " << arrival << endl;
	os << "service time: " << timeRequired << endl;
	os << "start time: " << startTime << endl;
	os << "end time: " << endTime << endl;
	os << "wait time: " << waitTime << endl;
	os << "turn around: " << turnAround << endl;
	return os.str();
}
