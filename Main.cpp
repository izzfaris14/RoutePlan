#include <iostream>
#include <vector>        
#include "FileParser.h"   
#include "ShuttleList.h"   
#include "PassList.h"     
#include "RoutePlanner.h"

using namespace std;

int main() {
    FileParser parser;
    cout << "Driverless Public Transport System" << endl;

    vector<Shuttle*> rawShuttles = parser.readShuttles("shuttle.txt");
    vector<Passenger*> rawPassengers = parser.readPassengers("passenger.txt");

    ShuttleList sList(rawShuttles);
    PassList pList(rawPassengers);

    RoutePlanner planner(sList, pList);
    planner.generateMatches();

    cout << "System compiled successfully. Matches generated." << endl;

    return 0;
}