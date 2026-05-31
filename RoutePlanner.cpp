#include<iostream>
#include "RoutePlanner.h"

using namespace std;

void RoutePlanner::readFile(string fileName) {
	//Load data into pManager and sManager
	pManager.loadFromFile(fileName);
	sManager.loadFromFile(fileName);
}

void RoutePlanner::generateMatchesMAtches(){
	//Generate matches between shuttles and passengers based on destination and time
	for (const auto& shuttle : sManager.getShuttles()) {
		for (const auto& passenger : pManager.getPassengers()) {
			Route route(shuttle, passenger);
			if (route.checkDest() == "Destination matches: " + shuttle.getDest()) {
				matchedRoutes.push_back(route);
			}
		}
	}
}

void RoutePlanner::editRAMShuttle(string id, string newDest, time_t newTime) {
	//Edit shuttle data in RAM based on ID
	for (auto& shuttle : sManager.getShuttles()) {
		if (shuttle.getId() == id) {
			shuttle.setDest(newDest);
			shuttle.setTime(newTime);
			break;
		}
	}
}

void RoutePlanner::editRAMPassenger(string id, string newDest, time_t newTime) {
	//Edit passenger data in RAM based on ID
	for (auto& passenger : pManager.getPassengers()) {
		if (passenger.getId() == id) {
			passenger.setDest(newDest);
			passenger.setTime(newTime);
			break;
		}
	}
}

void RoutePlanner::writeFile(string fileName) {
	//Write updated data back to file
	cout << "Writing updated data to file: " << fileName << endl;
}