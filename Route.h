#pragma once
#include <string>
#include <vector>
#include "Shuttle.h"
#include "Passenger.h"

using namespace std;

class Route {
    Shuttle* assignedShuttle;
    Passenger* assignedPassenger;

public:
    Route(Shuttle* s, Passenger* p);

    string checkDest() const;
    string checkTime() const;
};