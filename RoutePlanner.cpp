#include<iostream>
#include<fstream>
#include "RoutePlanner.h"

using namespace std;

void RoutePlanner::readFile(string fileName) {
	//Load data into pManager and sManager
	pManager.loadFromFile("passenger.txt");
	sManager.loadFromFile("shuttle.txt");
}

void RoutePlanner::generateMatches() {
	cout << "Generating matches between shuttles and passengers..." << endl;
	vector<Passenger>& passengers = pManager.getPassengers();
	vector<Shuttle>& shuttles = sManager.getShuttles();

	for (const auto& p : passengers) {
		for (const auto& s : shuttles) {
			if (p.getDest() == s.getDest()) {
				matchedRoutes.push_back(Route(s, p));
				break;
			}
		}
	}
	cout << "Matched" << matchedRoutes.size() << " routes." << endl;
}

void RoutePlanner::editRAMShuttle(string id, string newDest, string newTime) {
	cout << "Editing shuttle in RAM: ID=" << id << ", New Destination=" << newDest << ", New Time=" << newTime << endl;
	for (auto& s : sManager.getShuttles()) {
		if (s.getId() == id) {
			s = Shuttle(id, newDest, newTime);
			cout << "Updated shuttle " << id << " in RAM." << endl;
			return;
		}
	}
	cout << "Shuttle with ID " << id << " not found." << endl;
}

void RoutePlanner::editRAMPassenger(string id, string newDest, string newTime) {
	cout << "Editing passenger in RAM: ID=" << id << ", New Destination=" << newDest << ", New Time=" << newTime << endl;
	for (auto& p : pManager.getPassengers()) {
		if (p.getId() == id) {
			p = Passenger(id, newDest, newTime);
			cout << "Updated passenger " << id << " in RAM." << endl;
			return;
		}
	}
	cout << "Passenger with ID " << id << " not found." << endl;
}

void RoutePlanner::writeFile(string fileName) {
	ofstream outFile(fileName);
	if (!outFile.is_open()) {
		cerr << "Error opening file for writing: " << fileName << endl;
		return;
	}
	for (const auto& route : matchedRoutes) {
		outFile << route.checkDest() << ", " << route.checkTime() << endl;
	}
	outFile.close();
	cout << "Matched routes written to file: " << fileName << endl;
}