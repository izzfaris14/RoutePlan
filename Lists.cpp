
#include<iostream>
#include "ShuttleList.h"
#include "PassList.h"
#include <fstream>
#include <sstream>

using namespace std;

ShuttleList::ShuttleList(vector<Shuttle> loadedData) {
	shuttleDB = loadedData;
}

Shuttle ShuttleList::getShuttle(int index) const {
	return shuttleDB[index]; 
}

void ShuttleList::editShuttle(string id, Shuttle updated) {
	for (int i = 0; i < shuttleDB.size(); i++) {
		if (shuttleDB[i].getId() == id) {
			shuttleDB[i] = updated;
			break;
		}
	}
}

PassList::PassList(vector<Passenger> loadedData) {
	passDB = loadedData;
}

vector<Passenger> PassList::getPassengers() const {
	return passDB;
}

Passenger PassList::getPassenger(int index) const {
	return passDB[index];
}

void PassList::editPassenger(string id, Passenger updated) {
	for (int i = 0; i < passDB.size(); i++) {
		if (passDB[i].getId() == id) {
			passDB[i] = updated;
			break;
		}
	}
}