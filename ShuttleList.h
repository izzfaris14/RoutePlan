#pragma once
#include <vector>
#include <string>
#include "Shuttle.h"

using namespace std;

class ShuttleList {
    vector<Shuttle*> shuttleDB; // changed to pointers
public:
    // added missing constructor 
    ShuttleList(vector<Shuttle*> loadedData);

    //void loadFromFile(string fileName);
    const vector<Shuttle*>& getShuttles() const;
    Shuttle* getShuttle(int index) const;
    void editShuttle(string id, Shuttle* updatedShuttle);
	void addShuttle(Shuttle* newShuttle);
	bool deleteShuttle(string id);
};