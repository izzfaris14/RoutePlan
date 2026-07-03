#pragma once
#include <string>
#include <vector>
#include "Shuttle.h"
#include "Passenger.h"

using namespace std;

class Route {
    Shuttle* sManage;
    Passenger* pManage;

public:
    Route(Shuttle* s, Passenger* p);

    string getRouteString() const;
    Shuttle* getShuttle() const;
    Passenger* getPassenger() const;
    string checkDest() const;
    string checkTime() const;
};