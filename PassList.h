#pragma once
#include<vector>
#include<string>
#include"Passenger.h"

using namespace std;

class PassList {
	vector<Passenger> passFile;
public:
	void loadFromFile(string fileName);
	vector<Passenger>& getPassengers();
};