#pragma once
#include<string>
#include<ctime>
#include"Shuttle.h"
#include"Passenger.h"

using namespace std;

class Route {
	Shuttle* sManage; //pointer to reference an existing SHuttle
	Passenger* pManage; //collection of Passenger pointers
public:
	Route(Shuttle* s, vector<Passenger*> p);
	string checkDest() const;
	string checkTime() const;
};