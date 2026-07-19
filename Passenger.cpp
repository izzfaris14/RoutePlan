#include<iostream>
#include "Passenger.h"


Passenger::Passenger(std::string id, std::string dest, std::string timeStr, int groupSize) 
	: Entity(id, dest, timeStr), groupSize(groupSize) {
}

std::string Passenger::getDeets() const {
	return "Passenger ID: " + getId() + 
		", Dest " + getDest() + 
		", Time:" + getTimeStr()+
		", Size: " + std::to_string(groupSize);
}

int Passenger::getGroupSize() const {
	return groupSize;
}