#include "Route.h"


Route::Route(Shuttle* s): sManage(s) {}

void Route::addPassenger(Passenger* p) {
	pManage.push_back(p);
}
Shuttle* Route::getShuttle() const { return sManage; }

const std::vector<Passenger*>& Route::getPassengers() const { return pManage; }

int Route::getCurrentOccupancy() const {
	int total = 0;
	for (const auto& p : pManage) {
		total += p->getGroupSize();
	}
	return total;
}

std::string Route::getRouteString() const {
	std::string res = "Shuttle: " + sManage->getId() + " | Occupancy: " +
		std::to_string(getCurrentOccupancy()) + "/" + std::to_string(sManage->getCapacity()) + "\nPassengers: ";
	if (pManage.empty()) { res += "None"; }
	for (const auto& p : pManage) {
		res += p->getId();
	}
	return res;
}
