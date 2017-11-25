#pragma once
#include <string>
#include <vector>
#include "Job.h"

using namespace std;
class SchedAlgBase
{
protected:
	vector<Job> finishedJobs;
	double time = 0;
	double totalWait = 0;
	string algName = "None";
public:
	void print();
	void printJobs();
};

