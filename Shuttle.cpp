#include"Shuttle.h"

Shuttle::Shuttle(std::string id, std::string dest, std::string timeStr, int capacity)
	:Entity(id, dest, timeStr), cap(capacity) {
}

int Shuttle::getCapacity() const { return cap; }

std::string Shuttle::getDeets() const {
	return "Shuttle ID: " + getId() + ", Dest: " + getDest() +
		", Time: " + getTimeStr() + ", Capacity: " + std::to_string(cap);
}