#pragma once
#include<string>
#include<ctime>
#include"Shuttle.h"
#include"Passenger.h"

using namespace std;

class Route {
	Shuttle sManage;
	Passenger pManage;
public:
	Route(Shuttle s, Passenger p);
	string checkDest() const;
	time_t checkTime() const;
};