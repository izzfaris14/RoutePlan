#include "SchedRepo.h"
#include <iostream>
#include <algorithm>

// --- CREATE ---
void SchedRepo::addShuttle(std::unique_ptr<Shuttle> s) {
    shuttles.push_back(std::move(s));
}

void SchedRepo::addPassenger(std::unique_ptr<Passenger> p) {
    passengers.push_back(std::move(p));
}

void SchedRepo::addRoute(const Route& r) {
    matchedRoutes.push_back(r);
}

void SchedRepo::clearRoutes() {
    matchedRoutes.clear();
}

// --- UPDATE (EDIT) ---
bool SchedRepo::editShuttle(const std::string& id, const std::string& newDest, const std::string& newTime, int newCap) {
    for (auto& s : shuttles) {
        if (s->getId() == id) {
            // Re instantiate to update const-like properties or create setter methods in Entity.
            // Since we don't have setters for dest/time in Entity, we replace the object entirely.
            s = std::make_unique<Shuttle>(id, newDest, newTime, newCap);
            clearRoutes(); // Invalidate current schedules to prevent dangling pointers
            return true;
        }
    }
    return false;
}

bool SchedRepo::editPassenger(const std::string& id, const std::string& newDest, const std::string& newTime, int newSize) {
    for (auto& p : passengers) {
        if (p->getId() == id) {
            p = std::make_unique<Passenger>(id, newDest, newTime, newSize);
            clearRoutes(); // Invalidate current schedules
            return true;
        }
    }
    return false;
}

// --- DELETE ---
bool SchedRepo::removeShuttle(const std::string& id) {
    for (auto it = shuttles.begin(); it != shuttles.end(); ++it) {
        if ((*it)->getId() == id) {
            shuttles.erase(it);
            clearRoutes(); // Prevent Route objects from accessing deleted memory
            return true;
        }
    }
    return false;
}

bool SchedRepo::removePassenger(const std::string& id) {
    for (auto it = passengers.begin(); it != passengers.end(); ++it) {
        if ((*it)->getId() == id) {
            passengers.erase(it);
            clearRoutes(); // Prevent Route objects from accessing deleted memory
            return true;
        }
    }
    return false;
}

// --- READ (RETRIEVAL WITH BOUNDS CHECKING) ---
size_t SchedRepo::getShuttleCount() const {
    return shuttles.size();
}

Shuttle* SchedRepo::getShuttle(size_t index) const {
    if (index >= shuttles.size()) return nullptr; // Defensive programming
    return shuttles[index].get();
}

size_t SchedRepo::getPassengerCount() const {
    return passengers.size();
}

Passenger* SchedRepo::getPassenger(size_t index) const {
    if (index >= passengers.size()) return nullptr; // Defensive programming
    return passengers[index].get();
}

size_t SchedRepo::getRouteCount() const {
    return matchedRoutes.size();
}

const Route& SchedRepo::getRoute(size_t index) const {
    // Using .at() throws an out_of_range exception rather than causing a silent segfault
    return matchedRoutes.at(index);
}