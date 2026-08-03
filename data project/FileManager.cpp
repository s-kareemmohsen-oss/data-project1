#include "FileManager.h"
#include "SimulationEngine.h"
#include "Event.h"
#include <fstream>
#include <iostream>

using namespace std;

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

bool FileManager::LoadInput(string fileName, SimulationEngine* sim)
{
	ifstream input(fileName);

	if (!input.is_open())
	{
		cout << "Cannot open input file." << endl;
		return false;
	}

	int B;
	int SU;
	int WU;
	int PS;
	int PJ;

	input >> B >> SU >> WU >> PS >> PJ;


	int* doctorsCount = new int[B];

	for (int i = 0; i < B; i++)
	{
		input >> doctorsCount[i];
	}


	int totalDoctors = 0;

	for (int i = 0; i < B; i++)
		totalDoctors += doctorsCount[i];

	for (int i = 0; i < totalDoctors; i++)
	{
		int branch;
		char spec;
		int shift;
		int breakAfter;
		int breakDuration;

		input >> branch
			>> spec
			>> shift
			>> breakAfter
			>> breakDuration;

	}

	int autoEscalation;

	input >> autoEscalation;


	int events;

	input >> events;

	for (int i = 0; i < events; i++)
	{
		char eventType;

		input >> eventType;

		if (eventType == 'C')
		{
			char patientType;

			int time;
			int id;
			int branch;
			int tests;

			input >> patientType
				>> time
				>> id
				>> branch
				>> tests;

			Event* pEvent =
				new CheckInEvent(
					time,
					id,
					patientType,
					branch,
					tests);

			sim->addEvent(pEvent);
		}
		else if (eventType == 'L')
		{
			int time;
			int id;

			input >> time >> id;

			Event* pEvent =
				new LeaveEvent(
					time,
					id);

			sim->addEvent(pEvent);
		}
		else if (eventType == 'U')
		{
			int time;
			int id;

			input >> time >> id;

			Event* pEvent =
				new UrgentEvent(
					time,
					id);

			sim->addEvent(pEvent);
		}
	}

	delete[] doctorsCount;

	input.close();

	return true;
}

bool FileManager::SaveOutput(string fileName, SimulationEngine* sim)
{
	ofstream output(fileName);

	if (!output.is_open())
		return false;

	

	output.close();

	return true;
}