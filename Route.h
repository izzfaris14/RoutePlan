#pragma once
#include <string>
#include "Shuttle.h"
#include "Passenger.h"


class Route {
    Shuttle* sManage;
    Passenger* pManage;

public:
    Route(Shuttle* s, Passenger* p);
	
	std::string checkDest() const;
	std::string checkTime() const;
	std::string getRouteString() const;

	Shuttle* getShuttle() const;
	Passenger* getPassenger() const;
};