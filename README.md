# SchedulingAlgs
School Project for simulating operating system scheduling algorithms.

Project Description:

Project Directory Structure:

Top Level:

	schedulingalgs: contains all code
        
		makeandrun.bat: build and run project

		schedulingalgs.cpp: Contains main function.

		Job.cpp: Contains implementation of job class which stores all data for a single job
		Job.h: Contains Job class declaration

		fcfs.cpp: Contains FCFS algorithm class implementation
		fcfs.h: Contains FCFS algorithm class declaration

		sjf.cpp: Contains SJF algorithm class implementation
		sjf.h: Contains SJF class declaration
		
		RoundRobin.cpp: RoundRobin class implementation
		RoundRobin.h: RoundRobin class declaration

		SchedAlgBase.cpp: Scheduling algorithm base class implemenation
		SchedAlgBase.h: Scheduling algorithm base class declaration

		schedulingalgs.vcxproj: visual studio vcxproj file (contains build info when compiling with visual studio)
		schedulingalgs.vcxproj.filters: visual studio file for creating a file structure (files will be seperated into "fake" folders when opened with visual studio).
	
	schedulingalgs.sln: visual studio solution file

	reports:
		Results Table.xlsx: Contains results for test run. (using data from results.docx). Used to make graphs.
		Results.docx: Contains console output of test run
		scheduling algorithms presentation.pptx: contains power point presentation
		Team Project Topic One_ CPU Scheduling Algorithms Report.docx: contains written component of project.
		

Build Command:
makeandrun.bat (crossplatform)

run command:
./sim -d -a algorithmName inputfile

-If no input file is specified, generates input file
-If the -d flag is set, each process is printed
-If the -a flag is set only specified algorithm will be used
-Order doesnt matter except for input file which must be last
