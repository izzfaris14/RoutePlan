#include "Route.h"


Route::Route(Shuttle* s, Passenger* p) {
    this->assignedShuttle = s;
    this->assignedPassenger = p;
}

string Route::checkDest() const {
    // Check if the passenger pointer is null just to be safe
    if (assignedPassenger == nullptr) {
        return "No passengers assigned.";
    }

    if (assignedShuttle->getDest() == assignedPassenger->getDest()) {
        return "Destination matches: " + assignedShuttle->getDest();
    }
    else {
        return "Destination mismatched";
    }
} 

string Route::checkTime() const {
    return assignedShuttle->getTimeStr(); 
}

string Route::getRouteString() const {
    if (assignedShuttle == nullptr || assignedPassenger == nullptr) return "Invalid Route";
    return "Shuttle " + assignedShuttle->getId() + " (" + assignedShuttle->getDest() + " @ " + assignedShuttle->getTimeStr() +
        ") - Passenger " + assignedPassenger->getId() + " (" + assignedPassenger->getDest() + " @ " + assignedPassenger->getTimeStr() + ")";
}

Shuttle* Route::getShuttle() const {
    return assignedShuttle;
}

Passenger* Route::getPassenger() const {
    return assignedPassenger;
}