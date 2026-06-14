#include<iostream>
#include "Passenger.h"

using namespace std;

Passenger::Passenger(string id, string dest, string timeStr) : Entity(id, dest, timeStr) {
}

string Passenger::getDeets() const {
	return "Passenger ID: " + getId() + ", Dest " + getDest() + ", Time:" + getTimeStr();