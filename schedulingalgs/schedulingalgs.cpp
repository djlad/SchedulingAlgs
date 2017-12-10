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
	//read job from file
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

bool argsContain(char* argToCheck, int argc, char** argv) {
	//check if cmd line arg is in argv
	for (int i = 0; i < argc; i++) {
		if (strcmp(argToCheck, argv[i]) == 0) {
			return true;
		}
	}
	return false;
}

char* getArgJobFile(int argc, char** argv) {
	//get input job file from args
	char* lastArg = argv[argc - 1];
	char keyArgs[7][15] = {"RR10", "RR50", "RR100",
						   "FCFS", "SJF","-d", "-a"};
	for (int i = 0; i < 7; i++) {
		if (strcmp(keyArgs[i], lastArg) == 0 || argc == 1) {
			return "";
		}
	}
	return lastArg;
}

int main(int argc, char** argv)
{
	double contextSwitch;
	int numJobs;
	Job toRun;
	
	char* inputFile = getArgJobFile(argc, argv);
	//if no input file, generate input file
	if (strcmp("", inputFile) == 0) {
		generateJobs(100, 5);
		inputFile = "jobs.txt";
	}
	//open file read numJobs and contextSwitch
	fstream jobFile(inputFile);
	jobFile >> numJobs >> contextSwitch;
	
	//instantiate schedule simulation objects
	Fcfs fcfs(contextSwitch);
	Sjf sjf(contextSwitch);
	RoundRobin rr10(contextSwitch, 10);
	RoundRobin rr50(contextSwitch, 50);
	RoundRobin rr100(contextSwitch, 100);

	while (!jobFile.eof()) {
		//run all jobs
		toRun = readJob(jobFile);
		rr10.runJob(toRun);
		rr50.runJob(toRun);
		rr100.runJob(toRun);
		fcfs.runJob(toRun);
		sjf.runJob(toRun);
	}
	jobFile.close();
	//tell simulations there are no more jobs
	rr10.finish();
	rr50.finish();
	rr100.finish();
	sjf.finish();

	//parse arguments and print jobs
	bool runAll = !argsContain("-a", argc, argv);
	if (argsContain("RR10", argc, argv) || runAll) {
		rr10.print();
		if (argsContain("-d", argc, argv))rr10.printJobs();
	}
	if (argsContain("RR50", argc, argv) || runAll) {
		rr50.print();
		if (argsContain("-d", argc, argv))rr50.printJobs();
	}
	if (argsContain("RR100", argc, argv) || runAll) {
		rr100.print();
		if (argsContain("-d", argc, argv))rr100.printJobs();
	}
	if (argsContain("SJF", argc, argv) || runAll) {
		sjf.print();
		if (argsContain("-d", argc, argv))sjf.printJobs();
	}
	if (argsContain("FCFS", argc, argv) || runAll) {
		fcfs.print();
		if (argsContain("-d", argc, argv))fcfs.printJobs();
	}
	cout << getArgJobFile(argc, argv) << endl;
	
	//wait for input from user before termination
	system("pause");
    return 0;
}

