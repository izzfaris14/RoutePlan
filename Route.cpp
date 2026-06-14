#include "Route.h"

ROute::ROute(Shuttle* s, vector<Passenger*> p) {
	this->assignedShuttle = s;
	this->assignedPassengers = p;
}

string Route::checkDest() const {
	if (assignedPassengers.empty()) {
		return "No passengers assigned.";
}
	if (assignedShuttle->getDest() == assignedPassengers[0]->getDest()) {
		return "Destination mathces: " +assignedShuttle->getDest();
	}
	else {
		return "Destination mismatched";
	}

	string Route::checkTime() const {
		return assignedShuttle->getTimeStr();
	}