#include "Sjf.h"
#include <iostream>
using namespace std;

bool operator<(const Job a, const Job b){
	return a.timeRequired > b.timeRequired;
}

Job Sjf::calcJob(Job & j, double startTime)
{
	j.startTime = startTime;
	j.endTime = startTime + j.timeRequired;
	j.waitTime = startTime - j.arrival;
	j.waitTime = j.waitTime >= 0 ? j.waitTime : 0;
	j.turnAround = j.endTime - j.arrival;
	return j;
}

void Sjf::runJob(Job toRun)
{
	if (toRun.arrival <= time) {
		readyJobs.push(toRun);
		return;
	}
	
	Job futureJob = toRun;
	Job nextJob;
	//simulate all the jobs that are ready
	//and that can run before future job
	while (!readyJobs.empty()) {
		nextJob = readyJobs.top();
		readyJobs.pop();
		switchContext();
		nextJob = calcJob(nextJob, time);
		time += nextJob.timeRequired;
		finishedJobs.push_back(nextJob);
		if (time >= futureJob.arrival) {
			//if future job is no longer in the future
			break;
		}
	}
	//If no jobs to run except for future job
	//wait till future job has arrived
	if (time < futureJob.arrival) {
		totalIdleTime += futureJob.arrival - time;
		time = futureJob.arrival;
	}
	//move futureJob to ready
	readyJobs.push(futureJob);
}

void Sjf::finish()
{
	Job nextJob;
	while (!readyJobs.empty()) {
		nextJob = readyJobs.top();
		readyJobs.pop();
		switchContext();
		nextJob = calcJob(nextJob, time);
		time += nextJob.timeRequired;
		finishedJobs.push_back(nextJob);
	}
}


