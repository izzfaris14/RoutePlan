#pragma once
#include<vector>
#include<string>
#include"Passenger.h"

class PassList {
	vector<Passenger> passDB;
public:
	void loadFromFile(string fileName);
	const vector<Passenger>& getPassengers() const; //getter becomes encapsulation
	Passenger getPassenger(int index) const;
	void editPassenger(string id, Passenger updatedPassenger);
};