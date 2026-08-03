#include <iostream>
#include "SimulationEngine.h"
#include "FileManager.h"

using namespace std;

int main()
{
	SimulationEngine simulation;
	FileManager fileManager;

	if (!fileManager.LoadInput("sample1.txt", &simulation))
	{
		cout << "Failed to load input file." << endl;
		return -1;
	}

	cout << "Input file loaded successfully." << endl;
	simulation.RunSimulation();

	return 0;
}