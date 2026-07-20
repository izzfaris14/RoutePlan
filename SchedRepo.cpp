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

void SchedRepo::clearRoutes() {
	matchedRoutes.clear();
}

size_t SchedRepo::getShuttleCount() const { 
	return shuttles.size(); 
}
Shuttle* SchedRepo::getShuttle(size_t index) const { 
	return shuttles[index].get();
}

size_t SchedRepo::getPassengerCount() const {
	return passengers.size();
}
Passenger* SchedRepo::getPassenger(size_t index) const {
	return passengers[index].get();
}

size_t SchedRepo::getRouteCount() const {
	return matchedRoutes.size();
}
const Route& SchedRepo::getRoute(size_t index) const {
	return matchedRoutes[index];
}