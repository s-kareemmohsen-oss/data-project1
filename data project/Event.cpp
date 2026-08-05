#include "Event.h"
#include "Patient.h"
#include "Scheduler.h"
#include "SimulationEngine.h"

CheckInEvent::CheckInEvent(int time, int id, char pType, int b, int tests)
    : Event(time, id), type(pType), branch(b), numTests(tests) {
}

void CheckInEvent::Execute(SimulationEngine* pApp) {
    Patient* newPatient = new Patient(patientID, type, eventTime, branch, numTests);
    pApp->getScheduler()->addPatient(newPatient);
}

LeaveEvent::LeaveEvent(int time, int id) : Event(time, id) {

}

void LeaveEvent::Execute(SimulationEngine* pApp) {
    pApp->getScheduler()->removePatient(patientID);
}

UrgentEvent::UrgentEvent(int time, int id) : Event(time, id) {
}

void UrgentEvent::Execute(SimulationEngine* pApp) {
    pApp->getScheduler()->promoteToUrgent(patientID);
}