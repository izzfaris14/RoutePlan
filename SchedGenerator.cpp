#include "SchedGenerator.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

int SchedGenerator::parseTimeStr(const std::string& timeStr) const {
    if (timeStr.empty()) return 0;

    int hours = 0, minutes = 0;
    char colon;
    std::string period = timeStr.substr(timeStr.length() - 2); // Extract "am" or "pm"

    std::stringstream ss(timeStr.substr(0, timeStr.length() - 2));
    ss >> hours >> colon >> minutes;

    if (period == "pm" && hours != 12) hours += 12;
    if (period == "am" && hours == 12) hours = 0;

    return (hours * 60) + minutes;
}

void SchedGenerator::generateMatches(SchedRepo& repo, int algorithmMode) {
    // 1. STATE RESET: Clear the "assigned" flags and existing routes safely
    for (size_t i = 0; i < repo.getPassengerCount(); i++) {
        repo.getPassenger(i)->setAssigned(false);
    }
    for (size_t i = 0; i < repo.getShuttleCount(); i++) {
        repo.getShuttle(i)->setAssigned(false);
    }
    repo.clearRoutes(); // Prevent duplicate schedules in RAM

    // 2. EXTRACT AVAILABLE SHUTTLES
    std::vector<Shuttle*> availableShuttles;
    for (size_t i = 0; i < repo.getShuttleCount(); i++) {
        if (repo.getShuttle(i)->isAvailable()) {
            availableShuttles.push_back(repo.getShuttle(i));
        }
    }

    // 3. SORTING ENGINE: Apply the selected algorithmic option
    if (algorithmMode == 1) {
        // Option 1: Minimum Shuttle Dispatch (Sort by Capacity, Descending)
        std::sort(availableShuttles.begin(), availableShuttles.end(), [](Shuttle* a, Shuttle* b) {
            return a->getCapacity() > b->getCapacity();
            });
    }
    else if (algorithmMode == 2) {
        // Option 2: Passenger Arrival Time (Sort by Arrival Time, Ascending)
        std::sort(availableShuttles.begin(), availableShuttles.end(), [this](Shuttle* a, Shuttle* b) {
            return parseTimeStr(a->getTimeStr()) < parseTimeStr(b->getTimeStr());
            });
    }

    // 4. CORE MATCHING LOGIC
    for (Shuttle* s : availableShuttles) {
        if (!s->isAvailable()) continue;

        Route newRoute(s);
        int shuttleTime = parseTimeStr(s->getTimeStr());

        for (size_t j = 0; j < repo.getPassengerCount(); j++) {
            Passenger* p = repo.getPassenger(j);

            if (p->getIsAssigned()) continue;

            int passTime = parseTimeStr(p->getTimeStr());
            int timeDiff = passTime - shuttleTime;

            // Specification: Passengers can arrive at most 10 minutes early, but cannot be late.
            bool timeValid = (timeDiff >= 0 && timeDiff <= 10);

            if (p->getDest() == s->getDest() && timeValid) {
                // Ensure current occupancy + new group size does not exceed shuttle maximum capacity
                if (s->getCapacity() >= (newRoute.getCurrentOccupancy() + p->getGroupSize())) {
                    newRoute.addPassenger(p);
                    p->setAssigned(true);
                }
            }
        }

        if (newRoute.getPassengerCount() > 0) {
            repo.addRoute(newRoute);
            // Lock the shuttle if it has reached 100% capacity
            if (s->getCapacity() == newRoute.getCurrentOccupancy()) {
                s->setAssigned(true);
            }
        }
    }
}