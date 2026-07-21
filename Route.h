#pragma once
#include <string>
#include <vector>
#include "Shuttle.h"
#include "Passenger.h"

class Route {
private:
	Shuttle* sManage;
	std::vector<Passenger*> pManage;

public:
	Route(Shuttle* s);

	void addPassenger(Passenger* p);
	size_t getPassengerCount() const;
	std::string getRouteString() const;

	Shuttle* getShuttle() const;
	const std::vector<Passenger*>& getPassengers() const;
	int getCurrentOccupancy() const;
}; 