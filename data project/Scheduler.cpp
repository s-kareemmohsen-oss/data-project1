#include"Scheduler.h"
#include"Doctor.h"
void schedular::setConfig(int b, int su, int wu, int ps, int pj, int autoe) {
	numBranches = b;
	SU = su;
	WU = wu;
	PS = ps;
	PJ = pj;
	AutoE = autoe;
}

void schedular::addDoctor(doctor* d) {
	doclist.push_back(d);
}

void schedular::addPatient(Patient* p) {
	if (p->getType() == 'E') {
		emergencyQueue.push(p);
	}
	else {
		regularQueue.push(p);
	}
}

Patient* schedular::getHighestPriorityPatient(PriorityQueue<Patient*>& q, int branch) {
	PriorityQueue<Patient*> temp;
	Patient* found = nullptr;
	while (!q.empty()) {
		Patient* p = q.top();
		q.pop();
		if (p->getBranch() == branch) {
			found = p;
			break;
		}
		else {
			temp.push(p);
		}
	}
	while (!temp.empty()) {
		q.push(temp.top());
		temp.pop();
	}
	return found;
}

void schedular::autoEscalatePatients(int curr) {
	PriorityQueue<Patient*> tempQueue;
	while (!regularQueue.empty()) {
		Patient* p = regularQueue.top();
		regularQueue.pop();

		if (curr - p->getCheckInTime() >= AutoE) {
			p->setType('E');
			p->setAutoEsc(true);
			emergencyQueue.push(p);
		}
		else {
			tempQueue.push(p);
		}
	}
	while (!tempQueue.empty()) {
		regularQueue.push(tempQueue.top());
		tempQueue.pop();
	}
}
void schedular::promoteToUrgent(int id) {
	PriorityQueue<Patient*> temp;
	Patient* target = nullptr;
	while (!regularQueue.empty()) {
		Patient* p = regularQueue.top();
		regularQueue.pop();
		if (p->getId() == id) {
			target = p;
		}
		else {
			temp.push(p);
		}
	}
	while (!temp.empty()) {
		regularQueue.push(temp.top());
		temp.pop();
	}
	if (target != nullptr) {
		target->setType('E');
		emergencyQueue.push(target);
	}
}

bool schedular::removePatient(int id) {
	PriorityQueue<Patient*> temp;
	bool found = false;
	Patient* target = nullptr;
	while (!regularQueue.empty()) {
		Patient* p = regularQueue.top();
		regularQueue.pop();
		if (p->getId() == id) {
			found = true;
			target = p;
		}
		else {
			temp.push(p);
		}
	}
	while (!temp.empty()) {
		regularQueue.push(temp.top());
		temp.pop();
	}
	if (target != nullptr) {
		delete target;
	}
	return found;
}

bool schedular::isSimulationDone() {
	if (!emergencyQueue.empty() || !regularQueue.empty()) {
		return false;
	}
	for (int i = 0; i < doclist.size(); i++) {
		if (doclist.getAt(i)->get_cs() == busy) {
			return false;
		}
	}
	return true;
}
void schedular::updocst(int curr)
{
	for (int i = 0; i < doclist.size(); i++)
	{
		doctor* d = doclist.getAt(i);

		d->update_state(curr);

		if (d->get_cs() == idle && d->get_current_patient() != nullptr)
		{
			doneList.enqueue(d->release_patient());
		}
	}
}
void schedular::asspatients(int curr)
{
	for (int i = 0; i < doclist.size(); i++)
	{
		doctor* d = doclist.getAt(i);

		if (!d->is_available(curr))
			continue;

		Patient* p = nullptr;

		if (d->get_docspec() == 'S')
		{
			p = getHighestPriorityPatient(emergencyQueue, d->get_branch());

			if (!p)
				p = getHighestPriorityPatient(regularQueue, d->get_branch());
		}
		else
		{
			p = getHighestPriorityPatient(regularQueue, d->get_branch());

			if (!p)
				p = getHighestPriorityPatient(emergencyQueue, d->get_branch());
		}

		if (p)
			assignPatientToDoctor(p, d, curr);
	}
}
void schedular::assignPatientToDoctor(Patient* p, doctor* newdoc, int curr) {
	if (p == nullptr || newdoc == nullptr) return;
	int per_test_dur = (newdoc->get_docspec() == 'S') ? PS : PJ;
	newdoc->assign_patient(p, curr, SU, WU, per_test_dur);
}