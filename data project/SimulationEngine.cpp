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
    int mode;
    cout << "Select Run Mode:\n";
    cout << "1. Silent Mode\n";
    cout << "2. Interactive Mode\n";
    cout << "Enter 1 or 2: ";
    cin >> mode;
    cin.ignore();

    cout << "Simulation Started...\n";

    while (!eventQueue.empty() || !clinicScheduler->isSimulationDone()) {

        while (!eventQueue.empty() && eventQueue.front()->getEventTime() == currentTimestamp) {
            Event* currentEvent = eventQueue.front();
            eventQueue.dequeue();
            currentEvent->Execute(this);
            delete currentEvent;
        }

        clinicScheduler->autoEscalatePatients(currentTimestamp);
        clinicScheduler->updocst(currentTimestamp);
        clinicScheduler->asspatients(currentTimestamp);

        if (mode == 2) {
            clinicScheduler->printSnapshot(currentTimestamp);
            cout << "-- press Enter to continue --";
            cin.get();
        }

        currentTimestamp++;
    }

    cout << "Simulation Ended at timestamp: " << currentTimestamp - 1 << "\n";
}
bool SimulationEngine::Step()
{
    if (eventQueue.empty() && clinicScheduler->isSimulationDone())
        return false;

    while (!eventQueue.empty() &&
        eventQueue.front()->getEventTime() == currentTimestamp)
    {
        Event* currentEvent = eventQueue.front();
        eventQueue.dequeue();

        currentEvent->Execute(this);

        delete currentEvent;
    }

    clinicScheduler->autoEscalatePatients(currentTimestamp);
    clinicScheduler->updocst(currentTimestamp);
    clinicScheduler->asspatients(currentTimestamp);

    currentTimestamp++;

    return true;
}

void SimulationEngine::RunSilent()
{
    cout << "Simulation Started...\n";

    while (Step())
    {
    }

    cout << "Simulation Ended at timestamp: "
        << currentTimestamp - 1 << "\n";
}

void SimulationEngine::RunInteractive()
{
    cout << "Simulation Started...\n";

    while (Step())
    {
        clinicScheduler->printSnapshot(currentTimestamp - 1);

        cout << "-- press Enter to continue --";
        cin.get();
    }

    cout << "Simulation Ended at timestamp: "
        << currentTimestamp - 1 << "\n";
}
int SimulationEngine::getCurrentTimestamp() const
{
    return currentTimestamp;
}