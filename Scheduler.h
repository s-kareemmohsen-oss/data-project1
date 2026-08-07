#pragma once
#include"Queue.h"
#include"Doctor.h"
#include"LinkedList.h"
#include"Patient.h"
#include"PriorityQueue.h"

class schedular {

	LinkedList<doctor*> doclist;
public:
	int numBranches;
	int SU;
	int WU;
	int PS;
	int PJ;
	int AutoE;
	PriorityQueue<Patient*> emergencyQueue; 
	PriorityQueue<Patient*> regularQueue;
	Queue<Patient*> doneList;
	void updocst(int curr);
	void asspatients(int curr);
	void assignPatientToDoctor(Patient* p, doctor* d, int curr);
	void setConfig(int b, int su, int wu, int ps, int pj, int autoe);
	void addDoctor(doctor* d);
	void addPatient(Patient* p);
	void autoEscalatePatients(int curr);
	Patient* getHighestPriorityPatient(PriorityQueue<Patient*>& q, int branch);
	void promoteToUrgent(int id);
	bool removePatient(int id);
	bool isSimulationDone();
	void printSnapshot(int currentTime);
};