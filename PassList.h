#pragma once
#include<vector>
#include<string>
#include"Passenger.h"

using namespace std;

class PassList {
	vector<Passenger> passFile;
	vector<Passenger>& getPassengers() { return passFile; }
};