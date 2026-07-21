#include "Passenger.h"

/*
 * ============================================================================
 * Class: Passenger
 * Author: Izz Faris Putra Bin Maskhurin
 * Description: Derived from Entity. Represents a passenger group requesting
 * transit to a specific destination at a specific time.
 * ============================================================================
 */

Passenger::Passenger(const std::string& id, const std::string& dest, const std::string& timeStr, int gSize)
	: Entity(id, dest, timeStr), gSize(gSize) {
}

int Passenger::getGroupSize() const {
	return gSize;
}

int Passenger::getCapacity() const {
	return gSize;
}

std::string Passenger::getDeets() const {
	return "Passenger ID: " + getId() + ", Dest: " + getDest() +
		", Time: " + getTimeStr() + ", Capacity: " + std::to_string(gSize);
}

bool Passenger::isAvailable() const {
	return !getIsAssigned();
}