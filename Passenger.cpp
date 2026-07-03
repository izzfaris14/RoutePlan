#include<iostream>
#include "Passenger.h"


Passenger::Passenger(std::string id, std::string dest, std::string timeStr, int groupSize) 
	: Entity(id, dest, timeStr), groupSize(groupSize) {
}

std::string Passenger::getDeets() const {
	return "Passenger ID: " + id + ", Dest " + dest + ", Time:" + timeStr+", Size: " + std::to_string(groupSize);
}