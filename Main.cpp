#include <iostream>
#include "Routeplanner.h"
using namespace std;

int main() {
	cout << "Driverless Public Transport System" << endl;

	RoutePlanner planner;

	planner.readFile("system_data");

	planner.generateMatches();

	time_t currentTime = time(nullptr);
	planner.editRAMShuttle("511", "School", currentTime);
	planner.editRAMPassenger("P01", "Supermarket", currentTime);

	planner.writeFile("matched_routes_output.txt");
	cout << "test";

}