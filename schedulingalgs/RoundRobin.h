#pragma once
#include "SchedAlgBase.h"
#include "Job.h"
#include <deque>

class RoundRobin: public SchedAlgBase
{
	double timeQuantum;
	deque<Job> readyJobs;
	Job calcJob(Job &job, double startTime);
public:
	RoundRobin(double timeQuantum) :timeQuantum(timeQuantum) { algName = "Round Robin"; };
	void runJob(Job toRun);
	void finish();
};

