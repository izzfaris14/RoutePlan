#include "Shuttle.h"

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