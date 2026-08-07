#pragma once

#include "SimulationEngine.h"

class GUI
{
private:
    SimulationEngine* engine;
    bool running;
    bool finished;

public:
    GUI(SimulationEngine* simulationEngine);
    void Run();
};