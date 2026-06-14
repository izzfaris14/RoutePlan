#pragma once
#include <vector>
#include <string>
#include <ctime>
#include "PassList.h"
#include "ShuttleList.h"
#include "Route.h"
#include "FileParser.h"

class RoutePlanner {
	PassList pManager;
	ShuttleList sManager;
	vector<Route> matchedRoutes;
public:
	void initializeSystem(FileParser& parser);

	void generateMatches();

	void editShuttle(string id, string newDest, string newTime);
	void editPassenger(string id, string newDest, string newTime);
};
