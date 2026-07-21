#include "Shuttle.h"

/*
 * ============================================================================
 * Class: Shuttle
 * Author: Izz Faris Putra Bin Maskhurin
 * Description: Derived from Entity. Represents a driverless public transport
 * vehicle with a specific seating capacity and charging destination.
 * ============================================================================
 */


 /*
  * Function: Shuttle (Constructor)
  * Author: Izz Faris Putra Bin Maskhurin
  * Description: Initializes the child entity and forwards the core attributes up to the Entity base class constructor. Time Complexity: O(1)
  * Parameters: id, dest, timeStr, groupSize (or capacity)
  * Returns: N/A
  */
Shuttle::Shuttle(const std::string& id, const std::string& dest, const std::string& timeStr, int capacity)
	: Entity(id, dest, timeStr), cap(capacity) {
}

int Shuttle::getCapacity() const {
	return cap;
}

void Shuttle::setCapacity(int c) {
	cap = c;
}

bool Shuttle::isAvailable() const {
	return !getIsAssigned() && cap > 0;
}

std::string Shuttle::getDeets() const {
	return "Shuttle ID: " + getId() + ", Dest: " + getDest() +
		", Time: " + getTimeStr() + ", Capacity: " + std::to_string(cap);
}