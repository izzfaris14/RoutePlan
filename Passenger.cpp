#include "Passenger.h"

Passenger::Passenger(std::string id, std::string dest, std::string timeStr, int gSize)
	:Entity(id,dest,timeStr),gSize(gSize){ }

int Passenger::getGroupSize() const{ return gSize; }

std::string Passenger::getDeets() const {
	return "Passenger ID: " + getId() + ", Dest: " + getDest() +
		", Time: " + getTimeStr() + ", Capacity: " + std::to_string(gSize);
}
