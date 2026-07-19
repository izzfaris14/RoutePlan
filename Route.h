#pragma once
#include <string>
#include <vector>
#include "Shuttle.h"
#include "Passenger.h"


class Route {
    Shuttle* sManage;
    std::vector<Passenger*> pManage; //accepts multiple passengers

public:
	Route(Shuttle* s); //only needs shuttle to start

	void addPassenger(Passenger* p);
	std::string getRouteString() const;
	
	//std::string checkDest() const;
	//std::string checkTime() const;
	//std::string getRouteString() const;

	Shuttle* getShuttle() const;
	const std::vector<Passenger*>& getPassengers() const;
	int getCurrentOccupancy() const;

};