#pragma once
#include"Doctor.h"
#include"LinkedList.h"
#include"Patient.h"
#include"PriorityQueue.h"

class schedular {
	LinkedList<doctor*> doclist;
public:
	PriorityQueue<Patient*> emergencyQueue; // طابور الطوارئ
	PriorityQueue<Patient*> regularQueue;
	void updocst(int curr);
	void asspatients(int curr);
	void assignPatientToDoctor(Patient* p, doctor* d, int curr);
	void sim();
};