#include "stdafx.h"
#include "RoundRobin.h"
#include "Job.h"
#include <iostream>

using namespace std;

Job RoundRobin::calcJob(Job & job, double endTime)
{	
	job.endTime = endTime;
	job.turnAround = job.endTime - job.arrival;
	job.waitTime = job.turnAround - job.timeRequired;
	return job;
}

void RoundRobin::runJob(Job toRun)
{
	if (toRun.arrival <= time) {
		readyJobs.push_back(toRun);
		return;
	}
	Job futureJob = toRun;
	Job nextJob;
	while (!readyJobs.empty() && futureJob.arrival > time) {
		nextJob = readyJobs.front();
		readyJobs.pop_front();
		if (nextJob.timeRemaining == nextJob.timeRequired){
			nextJob.startTime = time;
		}
		nextJob.timeRemaining -= timeQuantum;
		if (nextJob.timeRemaining <= 0) {
			time = time + timeQuantum + nextJob.timeRemaining;
			nextJob = calcJob(nextJob, time);
			finishedJobs.push_back(nextJob);
		}
		else {
			time += timeQuantum;
			readyJobs.push_back(nextJob);
		}
	}
	if (time < futureJob.arrival){
		totalIdleTime += futureJob.arrival - time;
		time = futureJob.arrival;
	}
	readyJobs.push_front(futureJob);
}

void RoundRobin::finish() {
	Job nextJob;
	while (!readyJobs.empty()) {
		nextJob = readyJobs.front();
		readyJobs.pop_front();
		if (nextJob.timeRemaining == nextJob.timeRequired){
			nextJob.startTime = time;
		}
		nextJob.timeRemaining -= timeQuantum;
		if (nextJob.timeRemaining <= 0) {
			time = time + timeQuantum + nextJob.timeRemaining;
			nextJob = calcJob(nextJob, time);
			finishedJobs.push_back(nextJob);
		}
		else {
			time += timeQuantum;
			readyJobs.push_back(nextJob);
		}
	}
}
