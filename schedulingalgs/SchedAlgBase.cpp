#include "stdafx.h"
#include "SchedAlgBase.h"
#include <iostream>
using namespace std;
void SchedAlgBase::print()
{
	cout << algName <<": " << endl;
	cout << "Total Time Units: " << time << endl;
	cout << "CPU utilization: " << (time - totalIdleTime) / time << endl;
	cout << "Total Idle Time: " << totalIdleTime;
	cout << endl << endl;
}

void SchedAlgBase::printJobs()
{
	for (int i = 0; i < finishedJobs.size(); i++ ) {
		finishedJobs[i].print();
		cout << endl;
	}
}
