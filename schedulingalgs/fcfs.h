#pragma once
#include <vector>
#include <string>
#include "Job.h"
#include "SchedAlgBase.h"

using namespace std;
class Fcfs:public SchedAlgBase
{
	Job calcJob(Job &j, double startTime);
public:
	Fcfs() { algName = "FCFS"; };
	string runJob(Job toRun);
};

