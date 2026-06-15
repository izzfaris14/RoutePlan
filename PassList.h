#pragma once
#include <vector>
#include <string>
#include "Passenger.h"

using namespace std;

class PassList {
    vector<Passenger*> passDB; // changed to pointers
public:
    // added missing constructor 
    PassList(vector<Passenger*> loadedData);

    //void loadFromFile(string fileName);
    const vector<Passenger*>& getPassengers() const;
    Passenger* getPassenger(int index) const;
    void editPassenger(string id, Passenger* updatedPassenger);
};