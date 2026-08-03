#include "SimulationEngine.h"
#include "Scheduler.h" 
#include "Event.h"     
#include <iostream>

using namespace std;

SimulationEngine::SimulationEngine() {
    currentTimestamp = 1; 
    clinicScheduler = new schedular(); 
}

SimulationEngine::~SimulationEngine() {
    delete clinicScheduler;

    while (!eventQueue.empty()) {
        Event* temp = eventQueue.front();
        eventQueue.dequeue();
        delete temp;
    }
}

void SimulationEngine::addEvent(Event* pEvent) {
    eventQueue.enqueue(pEvent);
}

schedular* SimulationEngine::getScheduler() const {
    return clinicScheduler;
}

void SimulationEngine::RunSimulation() {
    cout << "Simulation Started...\n";

    while (!eventQueue.empty() ) {

        while (!eventQueue.empty() && eventQueue.front()->getEventTime() == currentTimestamp) {
            Event* currentEvent = eventQueue.front();
            eventQueue.dequeue();

            currentEvent->Execute(this);
            delete currentEvent; 
        }

       
        currentTimestamp++;
    }

    cout << "Simulation Ended at timestamp: " << currentTimestamp - 1 << "\n";
}