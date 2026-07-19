#include "SchedGenerator.h"
#include "Route.h"
#include <cctype>
#include <vector>

int SchedGenerator::parseTimeStr(const std::string& timeStr) const {
    if (timeStr.length() < 5) return 0;

    // Dynamically find the colon to safely split hours and minutes
    size_t colonPos = timeStr.find(':');
    if (colonPos == std::string::npos) return 0;

    int hours = std::stoi(timeStr.substr(0, colonPos));
    int mins = std::stoi(timeStr.substr(colonPos + 1, 2));

    std::string period = timeStr.substr(timeStr.length() - 2);
    for (auto& c : period) c = std::tolower(c); // Ensure lowercase

    if (period == "pm" && hours != 12) hours += 12;
    else if (period == "am" && hours == 12) hours = 0;

    return (hours * 60) + mins;
}

void SchedGenerator::generateMatches(SchedRepo& repo) {
    const auto& passengers = repo.getPassengers();
    const auto& shuttles = repo.getShuttles();

    // 1. Create an empty route for every shuttle
    std::vector<Route> activeRoutes;
    for (const auto& s : shuttles) {
        activeRoutes.push_back(Route(s.get()));
    }

    // 2. Distribute passengers into the routes
    for (const auto& p : passengers) {
        if (p->getIsAssigned()) continue;

        int pTime = parseTimeStr(p->getTimeStr());

        for (auto& route : activeRoutes) {
            Shuttle* s = route.getShuttle();

            // Check Destination
            if (p->getDest() == s->getDest()) {

                int sTime = parseTimeStr(s->getTimeStr());

                // Check Time Buffer: Shuttle leaves between PassengerTime-10 and PassengerTime
                if (sTime >= (pTime - 10) && sTime <= pTime) {

                    // Check Capacity (Current Occupancy + Passenger Group Size <= Max Shuttle Capacity)
                    if (route.getCurrentOccupancy() + p->getGroupSize() <= s->getCapacity()) {

                        route.addPassenger(p.get());
                        p->setAssigned(true);
                        break; // Move to the next passenger since this one is now seated
                    }
                }
            }
        }
    }

    // 3. Save successfully created routes back to the repository
    for (const auto& route : activeRoutes) {
        if (!route.getPassengers().empty()) { // Only save routes that have people
            route.getShuttle()->setAssigned(true);
            repo.addRoute(route);
        }
    }
}