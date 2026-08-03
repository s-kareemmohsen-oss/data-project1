#pragma once
#include <string>

using namespace std;

class SimulationEngine;

class FileManager
{
public:

	FileManager();
	~FileManager();

	bool LoadInput(string fileName, SimulationEngine* sim);

	bool SaveOutput(string fileName, SimulationEngine* sim);
}; 
