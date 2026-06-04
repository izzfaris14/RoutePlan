#include <iostream>
#include "Routeplanner.h"
using namespace std;

int main() {
	cout << "Driverless Public Transport System" << endl;

	RoutePlanner planner;

	planner.readFile("system_data");

	planner.generateMatches();
	planner.editRAMShuttle("S01", "School", "7:15am");
	planner.editRAMPassenger("P01", "Supermarket", "8:05am");

	planner.writeFile("matched_routes_output.txt");


}
