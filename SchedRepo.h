#pragma once
#include <vector>
#include <memory>
#include "Shuttle.h"
#include "Passenger.h"
#include "Route.h"

class ScheduleRepo
{
	std::vector<std::unique_ptr<Shuttle>> shuttles;
	std::vector<std::unique_ptr<Passenger>> passengers;
	std::vector<Route> matchedRoutes;

public:
	//add data to database
	void addShuttle(std::unique_ptr<Shuttle> s);
	void addPassenger(std::unique_ptr<Passenger> p);
	void addRoute(const Route& r);

	//retrieve data safely using const references
	const std::vector<std::unique_ptr<Shuttle>>& getShuttles() const;
	const std::vector<std::unique_ptr<Passenger>>& getPassengers() const;
	const std::vector<Route>& getRoutes() const;
};

