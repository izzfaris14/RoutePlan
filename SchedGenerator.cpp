#include "SchedGenerator.h"
#include <iostream>

using namespace std;

void SchedGenerator::generateMatches(SchedRepo& repo) {
    // 1. STATE RESET: Clear the "assigned" flags so we can rebuild from scratch safely
    for (size_t i = 0; i < repo.getPassengerCount(); i++) {
        repo.getPassenger(i)->setAssigned(false);
    }
    for (size_t i = 0; i < repo.getShuttleCount(); i++) {
        repo.getShuttle(i)->setAssigned(false);
    }

    // 2. Standard Part 2 Matching Logic
    for (size_t i = 0; i < repo.getShuttleCount(); i++) {
        Shuttle* s = repo.getShuttle(i);

        if (!s->isAvailable()) continue;

        Route newRoute(s);

        for (size_t j = 0; j < repo.getPassengerCount(); j++) {
            Passenger* p = repo.getPassenger(j);

            if (p->getIsAssigned()) continue;

            if (p->getDest() == s->getDest() && p->getTimeStr() == s->getTimeStr()) {

                // NON-DESTRUCTIVE MATH: Current Occupancy + New Group Size <= Max Capacity
                if (s->getCapacity() >= (newRoute.getCurrentOccupancy() + p->getGroupSize())) {
                    newRoute.addPassenger(p);
                    p->setAssigned(true);
                }
            }
        }

        if (newRoute.getPassengerCount() > 0) {
            repo.addRoute(newRoute);
            // If the route is 100% full, lock the shuttle so it can't be used again
            if (s->getCapacity() == newRoute.getCurrentOccupancy()) {
                s->setAssigned(true);
            }
        }
    }
}