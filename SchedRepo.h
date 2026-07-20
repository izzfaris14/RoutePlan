#pragma once
#include <vector>
#include <memory>
#include "Shuttle.h"
#include "Passenger.h"
#include "Route.h"

class SchedRepo
{
	std::vector<std::unique_ptr<Shuttle>> shuttles;
	std::vector<std::unique_ptr<Passenger>> passengers;
	std::vector<Route> matchedRoutes;

public:
	//add data to database
	void addShuttle(std::unique_ptr<Shuttle> s);
	void addPassenger(std::unique_ptr<Passenger> p);
	void addRoute(const Route& r);
	void clearRoutes(); //required before re-generating matches

	//encapsualtion retrieval (no raw vectors returned)
	size_t getShuttleCount() const;
	Shuttle* getShuttle(size_t index) const;

	size_t getPassengerCount() const;
	Passenger* getPassenger(size_t index) const;

	size_t getRouteCount() const;
	const Route& getRoute(size_t index) const;
};

