#include "SchedAlgBase.h"
#include <iostream>
using namespace std;
SchedAlgBase::SchedAlgBase(double contextSwitchTime):contextSwitchTime(contextSwitchTime){}

void SchedAlgBase::print()
{
	//print main details of simulation
	cout << "--------" << endl;
	cout << algName <<": " << endl;
	cout << "Total Time Units: " << time << endl;
	cout << "CPU utilization: " << getCPUUtilization()*100 << "%" << endl;
	cout << "Total Idle Time: " << totalIdleTime << endl;
	printMetrics();
	cout << endl;
}

void SchedAlgBase::printMetrics() {
	//print extra metrics of simulation (for testing and chart comparisons)
	cout << "Average Turn Around Time: " << getAvgTurnAround() << endl;
	cout << "Average Wait Time: " << getAvgWaitTime() << endl;
	cout << "Context Switches: " << contextSwitches << endl;
}

void SchedAlgBase::printJobs()
{
	//print all jobs
	for (int i = 0; i < finishedJobs.size(); i++ ) {
		finishedJobs[i].print();
		cout << endl;
	}
}

double SchedAlgBase::getAvgWaitTime()
{
	double totalWaitTime = 0;
	for (int i = 0; i < finishedJobs.size(); i++) {
		totalWaitTime += finishedJobs[i].waitTime;
	}
	return totalWaitTime / (double)finishedJobs.size();
}

double SchedAlgBase::getAvgTurnAround()
{
	double totalTurnAround = 0;
	for (int i = 0; i < finishedJobs.size(); i++) {
		totalTurnAround += finishedJobs[i].turnAround;
	}
	return totalTurnAround / (double)finishedJobs.size();
}

double SchedAlgBase::getCPUUtilization()
{
	return (time - totalIdleTime) / time;
}

void SchedAlgBase::switchContext()
{
	contextSwitches++;
	time += contextSwitchTime;
}
