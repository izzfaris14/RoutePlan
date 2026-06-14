#include <iostream>
#include "Routeplanner.h"
using namespace std;

int main() {
	FileParser parser;
	cout << "Driverless Public Transport System" << endl;

	RoutePlanner planner;

	planner.generateMatches();
	planner.editRAMPassenger("P01", "Supermarket", "8:05am");

	planner.writeFile("matched_routes_output.txt");


}
