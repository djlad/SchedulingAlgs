#pragma once
#include <string>
#include <vector>
#include "Job.h"

using namespace std;
class SchedAlgBase
{
private:
	double contextSwitchTime = 0;
protected:
	vector<Job> finishedJobs;
	double time = 0;
	double totalWait = 0;
	double totalIdleTime = 0;
	string algName = "None";
public:
	SchedAlgBase(double contextSwitchTime);
	void print();
	void printMetrics();
	void printJobs();
	double getAvgWaitTime();
	double getAvgTurnAround();
	double getCPUUtilization();
	void switchContext();
};

