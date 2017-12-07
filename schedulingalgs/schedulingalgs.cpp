// schedulingalgs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "job.h"
#include "fcfs.h"
#include "Sjf.h"
#include "RoundRobin.h"
#include <iostream>
#include <fstream>


Job readJob(fstream &jobs) {
	Job job(-1, -1);
	//Job job;
	jobs >> job.procId;
	jobs >> job.arrival;
	jobs >> job.timeRequired;
	job.timeRemaining = job.timeRequired;
	return job;
}


int main()
{
	Job toRun;
	Fcfs fcfs;
	Sjf sjf;
	RoundRobin rr(1);
	int numJobs, contextSwitch;
	fstream jobFile("jobs.txt");
	jobFile >> numJobs >> contextSwitch;
	while (!jobFile.eof()) {
		toRun = readJob(jobFile);
		rr.runJob(toRun);
		fcfs.runJob(toRun);
		sjf.runJob(toRun);
	}
	rr.finish();
	sjf.finish();
	
	rr.print();
	rr.printJobs();
	cout << "--------" << endl;
	sjf.print();
	sjf.printJobs();
	cout << "--------" << endl;
	fcfs.print();
	fcfs.printJobs();
	jobFile.close();

	int stopper;
	cin >> stopper;
    return 0;
}

