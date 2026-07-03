#include "SchedRepo.h"
#include <memory>
#include <vector>
#include <utility>

using std::unique_ptr;
using std::vector;
using std::move;

void SchedRepo::addShuttle(unique_ptr<Shuttle> s) {
	shuttles.push_back(move(s));
}

void SchedRepo::addPassenger(unique_ptr<Passenger> p) {
	passengers.push_back(move(p));
}

void SchedRepo::addRoute(const Route& r) {
	matchedRoutes.push_back(r);
}

const vector<unique_ptr<Shuttle>>& SchedRepo::getShuttles() const {
	return shuttles;
}

const vector<unique_ptr<Passenger>>& SchedRepo::getPassengers() const {
	return passengers;
}

const vector<Route>& SchedRepo::getRoutes() const {
	return matchedRoutes;
}