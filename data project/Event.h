#pragma once

class SimulationEngine; 

class Event {
protected:
    int eventTime;
    int patientID;
public:
    Event(int time, int id) : eventTime(time), patientID(id) {}
    virtual ~Event() {}

    int getEventTime() const { return eventTime; }
    int getPatientID() const { return patientID; }

    virtual void Execute(SimulationEngine* pApp) = 0;
};
class CheckInEvent : public Event {
private:
    char type;
    int branch;
    int numTests;
public:
    CheckInEvent(int time, int id, char pType, int b, int tests);
    void Execute(SimulationEngine* pApp) override;
};

class LeaveEvent : public Event {
public:
    LeaveEvent(int time, int id);
    void Execute(SimulationEngine* pApp) override;
};

class UrgentEvent : public Event {
public:
    UrgentEvent(int time, int id);
    void Execute(SimulationEngine* pApp) override;
};