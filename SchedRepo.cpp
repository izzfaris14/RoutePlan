#include "SchedRepo.h"


void SchedRepo::addShuttle(std::unique_ptr<Shuttle> s) {
	shuttles.push_back(std::move(s));
}

void SchedRepo::addPassenger(std::unique_ptr<Passenger> p) {
	passengers.push_back(std::move(p));
}

void SchedRepo::addRoute(const Route& r) {
	matchedRoutes.push_back(r);
}

const std::vector<unique_ptr<Shuttle>>& SchedRepo::getShuttles() const {
	return shuttles;
}

const std::vector<unique_ptr<Passenger>>& SchedRepo::getPassengers() const {
	return passengers;
}

const std::vector<Route>& SchedRepo::getRoutes() const {
	return matchedRoutes;
}