#include "Passenger.h"

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