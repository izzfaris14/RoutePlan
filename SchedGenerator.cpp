#include "SchedGenerator.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

int SchedGenerator::parseTimeStr(const std::string& timeStr) const {
    if (timeStr.empty()) return 0;

    int hours = 0, minutes = 0;
    char colon;
    std::string period = timeStr.substr(timeStr.length() - 2);

    std::stringstream ss(timeStr.substr(0, timeStr.length() - 2));
    ss >> hours >> colon >> minutes;

    if (period == "pm" && hours != 12) hours += 12; 
    if (period == "am" && hours == 12) hours = 0;

    return (hours * 60) + minutes;
}

void SchedGenerator::generateMatches(SchedRepo& repo, int algorithmMode) {
    for (size_t i = 0; i < repo.getPassengerCount(); i++) {
        repo.getPassenger(i)->setAssigned(false);
    }
    for (size_t i = 0; i < repo.getShuttleCount(); i++) {
        repo.getShuttle(i)->setAssigned(false);
    }
    repo.clearRoutes();

    std::vector<Shuttle*> availableShuttles;
    for (size_t i = 0; i < repo.getShuttleCount(); i++) {
        if (repo.getShuttle(i)->isAvailable()) {
            availableShuttles.push_back(repo.getShuttle(i));
        }
    }

    if (algorithmMode == 1) {
        std::sort(availableShuttles.begin(), availableShuttles.end(), [](Shuttle* a, Shuttle* b) {
            return a->getCapacity() > b->getCapacity();
            });
    }
    else if (algorithmMode == 2) {
        std::sort(availableShuttles.begin(), availableShuttles.end(), [this](Shuttle* a, Shuttle* b) {
            return parseTimeStr(a->getTimeStr()) < parseTimeStr(b->getTimeStr());
            });
    }

    for (Shuttle* s : availableShuttles) {
        if (!s->isAvailable()) continue;

        Route newRoute(s);
        int shuttleTime = parseTimeStr(s->getTimeStr());

        for (size_t j = 0; j < repo.getPassengerCount(); j++) {
            Passenger* p = repo.getPassenger(j);

            if (p->getIsAssigned()) continue;

            int passTime = parseTimeStr(p->getTimeStr());
            int shuttleTime = parseTimeStr(s->getTimeStr());
            int timeDiff = passTime - shuttleTime;

            //  midnight adjustment
            if (timeDiff < -720) {
                timeDiff += 1440;
            }
            else if (timeDiff > 720) {
                timeDiff -= 1440;
            }

            bool timeValid = (std::abs(timeDiff) <= 10);

            if (p->getDest() == s->getDest() && timeValid) {
                if (s->getCapacity() >= (newRoute.getCurrentOccupancy() + p->getGroupSize())) {
                    newRoute.addPassenger(p);
                    p->setAssigned(true);
                }
            }
        }

        if (newRoute.getPassengerCount() > 0) {
            repo.addRoute(newRoute);
            if (s->getCapacity() == newRoute.getCurrentOccupancy()) {
                s->setAssigned(true);
            }
        }
    }
}