//combined PassList & ShuttleList

#include<iostream>
#include "ShuttleList.h"
#include "PassList.h"

using namespace std;

void ShuttleList::loadFromFile(string fileName) {
	//Implementation to load shuttle data from a file
	cout << "Loading shuttle data from file: " << fileName << endl;
}

vector<Shuttle>& ShuttleList::getShuttles() {
	return shuttleFile;
}

void PassList::loadFromFile(string fileName) {
	//Implementation to load passenger data from a file
	cout << "Loading passenger data from file: " << fileName << endl;
}

vector<Passenger>& PassList::getPassengers() {
	return passFile;
}