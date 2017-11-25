#pragma once
#include "SchedAlgBase.h"
#include "Job.h"
#include <queue>

class RoundRobin: public SchedAlgBase
{
	double timeQuantum;
	queue<Job> readyJobs;
	Job calcJob(Job &job, double startTime);
public:
	RoundRobin(double timeQuantum) :timeQuantum(timeQuantum) { algName = "Round Robin"; };
	void runJob(Job toRun);
	void finish();
};

