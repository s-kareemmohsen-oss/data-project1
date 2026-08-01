#include "Patient.h"
#include <iostream>
using namespace std;
using namespace std;
Patient::Patient() :id(0), type('R'), checkintime(0), branch(0), numtests(0), waitingtime(0), visittime(0), finishtime(0), autoesc(false){}
Patient::Patient(int pid, char ptype, int checktime, int b, int ptests) :
	id(pid), type(ptype), checkintime(checktime), branch(b), numtests(ptests), waitingtime(0), visittime(0), finishtime(0), autoesc(false) {}
int Patient::getId() const{ return id; }
char Patient::getType() const { return type; }
int Patient::getCheckInTime()const { return checkintime; }
int Patient::getBranch()const { return branch; }
int Patient::getNumTest()const { return numtests; }
int Patient::getWaitingTime()const { return waitingtime; }
int Patient::getVisitTime()const { return visittime; }
int Patient::getFinishTime()const { return finishtime; }
bool Patient::isAutoEsc()const{ return autoesc; }
void Patient::setType(char other) { type = other; }
void Patient::setWaitingTime(int other) { waitingtime = other; }
void Patient::setVisitTime(int vt){visittime = vt;}
void Patient::setFinshTime(int fh) { finishtime = fh; }
void Patient::setAutoEsc(bool other) { autoesc = other; }
double Patient::getPriority() const{
	if (type == 'E') {
		return -1 * checkintime;
	}
	return ( - 100 * checkintime) - (10 * numtests);
}
bool Patient::operator>(const Patient& other) const {
    return getPriority() > other.getPriority();
}

bool Patient::operator<(const Patient& other) const {
    return getPriority() < other.getPriority();
}

bool Patient::operator>=(const Patient& other) const {
    return getPriority() >= other.getPriority();
}

bool Patient::operator<=(const Patient& other) const {
    return getPriority() <= other.getPriority();
}

bool Patient::operator==(const Patient& other) const {
    return id == other.id;
}

void Patient::print() const {
    cout << "Patient ID: " << id
        << " | Type: " << type
        << " | CT: " << checkintime
        << " | Branch: " << branch
        << " | Tests: " << numtests << "\n";
}
