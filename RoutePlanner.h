#pragma once
#include <vector>
#include <string>
#include <ctime>
#include "PassList.h"
#include "ShuttleList.h"
#include "Route.h"
#include "FileParser.h"

using namespace std;

class RoutePlanner {
    PassList pManager;
    ShuttleList sManager;
    vector<Route> matchedRoutes;
public:
    RoutePlanner(ShuttleList sList, PassList pList);
    void writeFile(string fileName);
    void initializeSystem(FileParser& parser);
    void generateMatches();
    void editShuttle(string id, string newDest, string newTime);
    void editPassenger(string id, string newDest, string newTime);
};