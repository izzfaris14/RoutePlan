#include"Shuttle.h"
#include<iostream>


using namespace std;

Shuttle::Shuttle(std::string id, std::string dest, std::string timeStr, int capacity) : Entity(id, dest, timeStr), capacity(capacity) {}

int Shuttle::getCapacity() const { return capacity; }
string Shuttle::getDeets() const {
	return "Shuttle ID: " + getId() + ", Dest " + getDest() + ", Time:" + getTimeStr()+", capacity: "+std::to_string(capacity);
}