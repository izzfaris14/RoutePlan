#pragma once
#include <vector>
#include <string>
#include "Shuttle.h"

class ShuttleList {
	vector<Shuttle> shuttleDB;
public:
	void loadFromFile(string fileName);
	const vector<Shuttle>& getShuttles() const; //getter becomes encapsulation
	Shuttle getShuttle(int index) const; 
	void editShuttle(string id, Shuttle updatedShuttle);
};