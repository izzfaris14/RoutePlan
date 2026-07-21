#include "SchedRepo.h"
#include <iostream>
#include <algorithm>

/*
 * ============================================================================
 * Class: SchedRepo
 * Author: Leong Ming Foong
 * Description: Central data repository managing the lifecycle, memory, and
 * in-memory storage of all Passenger, Shuttle, and Route objects.
 * ============================================================================
 */

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

bool SchedRepo::editShuttle(const std::string& id, const std::string& newDest, const std::string& newTime, int newCap) {
    for (auto& s : shuttles) {
        if (s->getId() == id) {
            s = std::make_unique<Shuttle>(id, newDest, newTime, newCap);
            clearRoutes(); 
            return true;
        }
    }
    return false;
}

bool SchedRepo::editPassenger(const std::string& id, const std::string& newDest, const std::string& newTime, int newSize) {
    for (auto& p : passengers) {
        if (p->getId() == id) {
            p = std::make_unique<Passenger>(id, newDest, newTime, newSize);
            clearRoutes(); 
            return true;
        }
    }
    return false;
}

bool SchedRepo::removeShuttle(const std::string& id) {
    for (auto it = shuttles.begin(); it != shuttles.end(); ++it) {
        if ((*it)->getId() == id) {
            shuttles.erase(it);
            clearRoutes(); 
            return true;
        }
    }
    return false;
}

bool SchedRepo::removePassenger(const std::string& id) {
    for (auto it = passengers.begin(); it != passengers.end(); ++it) {
        if ((*it)->getId() == id) {
            passengers.erase(it);
            clearRoutes(); 
            return true;
        }
    }
    return false;
}

size_t SchedRepo::getShuttleCount() const {
    return shuttles.size();
}

Shuttle* SchedRepo::getShuttle(size_t index) const {
    if (index >= shuttles.size()) return nullptr; 
    return shuttles[index].get();
}

Shuttle* SchedRepo::getShuttleById(const std::string& id) const {
    for (const auto& s : shuttles) {
        if (s->getId() == id) {
            return s.get();
        }
    }
    return nullptr;
}

size_t SchedRepo::getPassengerCount() const {
    return passengers.size();
}

Passenger* SchedRepo::getPassenger(size_t index) const {
    if (index >= passengers.size()) return nullptr; 
    return passengers[index].get();
}

Passenger* SchedRepo::getPassengerById(const std::string& id) const {
    for (const auto& p : passengers) {
        if (p->getId() == id) {
            return p.get();
        }
    }
    return nullptr;
}

size_t SchedRepo::getRouteCount() const {
    return matchedRoutes.size();
}

const Route& SchedRepo::getRoute(size_t index) const {
    return matchedRoutes.at(index);
}