#include <iostream>
#include "Routeplanner.h"
using namespace std;

int main() {
	FileParser parser;
	cout << "Driverless Public Transport System" << endl;
	vector<Shuttle> rawShuttles = parser.readShuttles("shuttle.txt");
	vector<Passenger> rawPassengers = parser.readPassengers("passengers.txt");

	ShuttleList sList(rawShuttles);
	PassList pList(rawPassengers);

	RoutePlanner planner(sList, pList);

	planner.generateMatches();

	cout << "System compiled successfully. Matches generated." << endl;

}
