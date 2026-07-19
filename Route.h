#pragma once
#include <string>
#include <vector>
#include "Shuttle.h"
#include "Passenger.h"

class Route {
	Shuttle* sManage;
	std::vector<Passenger*> pManage;

public:
	Route(Shuttle* s);

	void addPassenger(Passenger* p);
	std::string getRouteString() const;

	Shuttle* getShuttle() const;
	const std::vector<Passenger*>& getPassengers() const;
	int getCurrentOccupancy() const;
};