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
		readyJobs.push(toRun);
		return;
	}
	Job futureJob = toRun;
	Job nextJob;
	while (!readyJobs.empty() && futureJob.arrival > time) {
		nextJob = readyJobs.front();
		readyJobs.pop();
		cout << "time: " << time<<endl;
		for (int i = 0; i < readyJobs.size(); i++){
			//cout << readyJobs[i] << " " << endl;
		}
		nextJob.print();
		cout << endl;
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
			readyJobs.push(nextJob);
		}
	}
	if (time < futureJob.arrival){
		time = futureJob.arrival;
	}
	readyJobs.push(futureJob);
}

void RoundRobin::finish() {
	Job nextJob;
	while (!readyJobs.empty()) {
		nextJob = readyJobs.front();
		readyJobs.pop();
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
			readyJobs.push(nextJob);
		}
	}
}
