// schedulingalgs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "job.h"
#include "fcfs.h"
#include "Sjf.h"
#include "RoundRobin.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <math.h>


Job readJob(fstream &jobs) {
	Job job(-1, -1);
	jobs >> job.procId;
	jobs >> job.arrival;
	jobs >> job.timeRequired;
	job.timeRemaining = job.timeRequired;
	return job;
}

double genExponentialDist(double mean) {
	//returns numbers following
	//exponential distribution (I think)
	static uniform_real_distribution<double> distribution(0.0,1.0);
	static default_random_engine generator;
	double uniform = distribution(generator);
	return -log(1 - uniform) * mean;
}

void generateJobs(int numJobs, double contextSwitchTime) {
	fstream f("jobs.txt", ios::out);
	int maxTimeRequired = 100;
	int minTimeRequired = 5;
	int timeRequired;
	int time = 0;
	int nextJobTime = 0;
	f << numJobs << "\t" << contextSwitchTime;
	for (int i = 0; i < numJobs; i++) {
		//create normally distributed time required
		timeRequired = rand() % (maxTimeRequired-minTimeRequired) + minTimeRequired;
		f << endl <<i << "\t" << nextJobTime << "\t" << timeRequired;
		time = nextJobTime;
		//set next job arrival to a exponentially distributed
		//amount of time in the future
		nextJobTime = time + genExponentialDist(100);
	}
	f.close();
}


int main()
{
	double contextSwitch;
	int numJobs;
	Job toRun;

	generateJobs(10000, 10);
	fstream jobFile("jobs.txt");
	jobFile >> numJobs >> contextSwitch;

	Fcfs fcfs(contextSwitch);
	Sjf sjf(contextSwitch);
	RoundRobin rr10(contextSwitch, 10);
	RoundRobin rr50(contextSwitch, 50);
	RoundRobin rr100(contextSwitch, 100);

	while (!jobFile.eof()) {
		toRun = readJob(jobFile);
		rr10.runJob(toRun);
		rr50.runJob(toRun);
		rr100.runJob(toRun);
		fcfs.runJob(toRun);
		sjf.runJob(toRun);
	}
	jobFile.close();

	rr10.finish();
	rr50.finish();
	rr100.finish();
	sjf.finish();
	
	rr10.print();
	//rr10.printJobs();
	cout << "--------" << endl;
	rr50.print();
	//rr50.printJobs();
	cout << "--------" << endl;
	rr100.print();
	//rr100.printJobs();
	cout << "--------" << endl;
	sjf.print();
	//sjf.printJobs();
	cout << "--------" << endl;
	fcfs.print();
	//fcfs.printJobs();

	int stopper;
	cin >> stopper;
    return 0;
}

