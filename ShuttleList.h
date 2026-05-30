#pragma once
#include <vector>
#include <string>
#include "Shuttle.h"

using namespace std;

class ShuttleList {
	vector<Shuttle> shuttleFile;
public:
	void loadFromFile(string fileName);
	vector<Shuttle> getShuttles() const { return shuttleFile; }
};