#pragma once
#include"Doctor.h"
#include"LinkedList.h"
class schedular {
	LinkedList<doctor*> doclist;
public:
	void updocst(int curr);
};