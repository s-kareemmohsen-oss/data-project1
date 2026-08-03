#pragma once
#include "Queue.h"

class schedular;
class Event;
class SimulationEngine {
private:
    int currentTimestamp;
    Queue<Event*> eventQueue;
    schedular* clinicScheduler; 

public:
    SimulationEngine();
    ~SimulationEngine();

    void addEvent(Event* pEvent);
    schedular* getScheduler() const;

    void RunSimulation();
};