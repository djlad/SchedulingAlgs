#include "stdafx.h"
#include "fcfs.h"



Job Fcfs::calcJob(Job & j, double startTime)
{
	j.startTime = startTime;
	j.endTime = startTime + j.timeRequired;
	j.waitTime = startTime - j.arrival;
	j.waitTime = j.waitTime >= 0 ? j.waitTime : 0;
	j.turnAround = j.endTime - j.arrival;
	return j;
}

string Fcfs::runJob(Job toRun)
{	
	if (toRun.arrival > time) {
		totalIdleTime += toRun.arrival - time;
		time = toRun.arrival;
	}
	switchContext();//pass time for context switch
	toRun = calcJob(toRun, time);
	time += toRun.timeRequired;
	totalWait += toRun.waitTime;
	finishedJobs.push_back(toRun);
	return toRun.toStr();
}

