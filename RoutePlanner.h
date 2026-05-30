#pragma once
#include <vector>
#include <string>
#include <ctime>
#include "PassList.h"
#include "ShuttleList.h"
#include "Route.h"

class RoutePlanner {
	PassList pManager;
	ShuttleList sManager;
	vector<Route> matchedRoutes;
public:
	void readFile(string fileName);
	void generateMatches();
	void editRAMShuttle(string id, string newDest, time_t newTime);
	void editRAMPassenger(string id, string newDest, time_t newTime);
	void writeFile(string fileName);
};
