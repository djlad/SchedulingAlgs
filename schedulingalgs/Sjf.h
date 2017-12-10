#pragma once
#include <vector>
#include <queue>
#include "Job.h"
#include "SchedAlgBase.h"

class Sjf: public SchedAlgBase
{
private:
	priority_queue<Job> readyJobs;
	Job calcJob(Job & j, double startTime);
public:
	Sjf(double contextSwitchTime):SchedAlgBase(contextSwitchTime) { algName = "Sjf"; }
	void runJob(Job toRun);
	void finish();
};

