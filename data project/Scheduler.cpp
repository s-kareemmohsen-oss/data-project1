#include"Scheduler.h"

void schedular::updocst(int curr) {
	for (int i = 0; i < doclist.size(); i++) {
		doctor* newdoc = doclist.getAt(i);
		if (newdoc->get_cs() == shift_not_started) {
			if (curr == newdoc->shst_t) {
				newdoc->set_cs(idle);
			}
		}
			else if(newdoc->get_cs() == busy){
				if (curr >= newdoc->get_et()) {
					newdoc->set_treated(newdoc->get_tp() + 1);
				if (newdoc->get_tp() == newdoc->breakafter) {
					newdoc->set_cs(onbreak);
					newdoc->set_treated(0);
					newdoc->set_eb(curr + newdoc->break_duration);
				}
				else {
					newdoc->set_cs(idle);

				}
				}
			}
			else if(newdoc->get_cs()==onbreak){
				if (curr >= newdoc->get_eb()) {
					newdoc->set_cs(idle);
				}
			}
		}
	}
//ناقص بس 					assignPatientToDoctor(p, newdoc, curr);
//هعملها بكرا عشان لسه مش فاهم اوي هعملها ازاي
void schedular::asspatients(int curr){
	for (int i = 0; i < doclist.size(); i++) {
		doctor* newdoc = doclist.getAt(i);
		if (newdoc->get_cs() == idle) {
			if (newdoc->get_docspec() == 'S') {
				if (!emergencyQueue.empty()) {
					Patient* p = emergencyQueue.top();
					emergencyQueue.pop();
					assignPatientToDoctor(p, newdoc, curr);
				}
				else if (!regularQueue.empty()) {
					Patient* p = regularQueue.top();
					regularQueue.pop();
					assignPatientToDoctor(p, newdoc, curr);
				}
			}
			else if (newdoc->get_docspec() == 'J') {
				if (!regularQueue.empty()) {
					Patient* p = regularQueue.top();
					regularQueue.pop();
					assignPatientToDoctor(p, newdoc, curr);
				}
				else if (!emergencyQueue.empty()) {
					Patient* p = emergencyQueue.top();
					emergencyQueue.pop();
					assignPatientToDoctor(p,newdoc, curr);
				}
			}
			}
		}
	}
void schedular::assignPatientToDoctor(Patient* p, doctor* newdoc, int curr) {
}