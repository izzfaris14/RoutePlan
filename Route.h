#pragma once
#include <string>
#include <vector>
#include "Shuttle.h"
#include "Passenger.h"

/*
 * ============================================================================
 * Class: Route
 * Author: Izz Faris Putra Bin Maskhurin
 * Description: Represents a successfully matched route, aggregating a single
 * driverless shuttle and its assigned collection of passengers.
 * ============================================================================
 */

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