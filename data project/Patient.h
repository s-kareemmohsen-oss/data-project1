#pragma once
class Patient {
private:
	int id;
	char type;
	int checkintime;
	int branch;
	int numtests;
	int waitingtime;
	int visittime;
	int finishtime;
	bool autoesc;
public:
	Patient();
	Patient(int pid, char ptype, int checktime, int b, int ptests);
	int getId() const;
	char getType() const;
	int getCheckInTime()const;
	int getBranch() const;
	int getNumTest()const;
	int getWaitingTime()const;
	int getVisitTime()const;
	int getFinishTime()const;
	bool isAutoEsc()const;
	void setType(char other);
	void setWaitingTime(int other);
	void setFinshTime(int fh);
	void setAutoEsc(bool other);
	void setVisitTime(int vt);
	double getPriority()const;
	bool operator>(const Patient& other)const;
	bool operator<(const Patient& other)const;
	bool operator<=(const Patient& other)const;
	bool operator>=(const Patient& other)const;
	bool operator==(const Patient& other)const;
	void print()const;
};