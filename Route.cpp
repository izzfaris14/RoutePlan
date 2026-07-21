#include "Route.h"
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


 /*
  * Function: Route (Constructor)
  * Author: Izz Faris Putra Bin Maskhurin
  * Description: Initializes a Route wrapping a single Shuttle pointer. Time Complexity: O(1)
  * Parameters: s (Shuttle*)
  * Returns: N/A
  */
Route::Route(Shuttle* s) : sManage(s) {}


/*
 * Function: addPassenger
 * Author: Izz Faris Putra Bin Maskhurin
 * Description: Appends a matched Passenger pointer to the route's collection. Time Complexity: O(1) amortized
 * Parameters: p (Passenger*)
 * Returns: void
 */
void Route::addPassenger(Passenger* p) {
	if (p != nullptr) {
		pManage.push_back(p);
	}
}

size_t Route::getPassengerCount() const {
	return pManage.size();
}

Shuttle* Route::getShuttle() const {
	return sManage;
}

const std::vector<Passenger*>& Route::getPassengers() const {
	return pManage;
}

int Route::getCurrentOccupancy() const {
	int total = 0;
	for (const auto& p : pManage) {
		total += p->getGroupSize();
	}
	return total;
}

std::string Route::getRouteString() const {
	std::string res = "Shuttle: " + sManage->getId() + " | Occupancy: " +
		std::to_string(getCurrentOccupancy()) + "/" + std::to_string(sManage->getCapacity()) + "\nPassenger:";

	if (pManage.empty()) {
		res += "None";
	}

	for (const auto& p : pManage) {
		res += " " + p->getId();
	}
	return res;
}