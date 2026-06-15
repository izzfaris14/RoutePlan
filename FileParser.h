#pragma once
#include <string>
#include <vector>
#include "Passenger.h"
#include "Shuttle.h"

using namespace std;

class FileParser {
public:
    vector<Passenger*> readPassengers(string fileName);
    vector<Shuttle*> readShuttles(string fileName);
};