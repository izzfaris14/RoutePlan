#include "Route.h"

// Fixed typo: ROute -> Route
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
} // <-- ADDED THIS MISSING BRACE!

string Route::checkTime() const {
    return assignedShuttle->getTimeStr(); // Assuming getTimeStr() exists in Shuttle.h
}