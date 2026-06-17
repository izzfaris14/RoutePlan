#include <iostream>
#include <vector>
#include <string>
#include "ShuttleList.h"
#include "PassList.h"

using namespace std;

// -- SHUTTLE LIST --
ShuttleList::ShuttleList(vector<Shuttle*> loadedData) {
    shuttleDB = loadedData;
}

const vector<Shuttle*>& ShuttleList::getShuttles() const {
    return shuttleDB;
}

Shuttle* ShuttleList::getShuttle(int index) const {
    return shuttleDB[index];
}

void ShuttleList::editShuttle(string id, Shuttle* updated) {
    for (int i = 0; i < shuttleDB.size(); i++) {
        if (shuttleDB[i]->getId() == id) {
            delete shuttleDB[i]; // Prevent memory leak
            shuttleDB[i] = updated;
            break;
        }
    }
}

void ShuttleList::addShuttle(Shuttle* newShuttle) {
	shuttleDB.push_back(newShuttle);
}

bool ShuttleList::deleteShuttle(string id) {
	for (int i = 0; i < shuttleDB.size(); i++) {
		if (shuttleDB[i]->getId() == id) {
			delete shuttleDB[i]; // Prevent memory leak
			shuttleDB.erase(shuttleDB.begin() + i);
			return true;
		}
	}
	return false; // Shuttle not found
}

// -- PASSENGER LIST --
PassList::PassList(vector<Passenger*> loadedData) {
    passDB = loadedData;
}

const vector<Passenger*>& PassList::getPassengers() const {
    return passDB;
}

Passenger* PassList::getPassenger(int index) const {
    return passDB[index];
}

void PassList::editPassenger(string id, Passenger* updated) {
    for (int i = 0; i < passDB.size(); i++) {
        if (passDB[i]->getId() == id) {
            delete passDB[i]; // Prevent memory leak
            passDB[i] = updated;
            break;
        }
    }
}

void PassList::addPassenger(Passenger* newPassenger) {
	passDB.push_back(newPassenger);
}

bool PassList::deletePassenger(string id) {
	for (int i = 0; i < passDB.size(); i++) {
		if (passDB[i]->getId() == id) {
			delete passDB[i]; // Prevent memory leak
			passDB.erase(passDB.begin() + i);
			return true;
		}
	}
	return false; // Passenger not found
}