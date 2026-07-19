#include "SchedGenerator.h"
#include "Route.h"
#include <cctype>
#include <vector>

int SchedGenerator::parseTimeStr(const std::string& timeStr) const {
	if (timeStr.length() < 5) return 0;

	size_t colonPos = timeStr.find(":");
	if (colonPos == std::string::npos)return 0;

	int hours = std::stoi(timeStr.substr(0, colonPos));
	int mins = std::stoi(timeStr.substr(colonPos + 1, 2));

	std::string period = timeStr.substr(timeStr.length() - 2);
	for (auto& c : period) c = std::tolower(c);

	if (period == "pm" && hours != 12) hours += 12;
	else if (period == "am" && hours == 12)hours = 0;

	return (hours * 60) + mins;
}

void SchedGenerator::generateMatches(SchedRepo& repo) {
	const auto& passengers = repo.getPassengers();
	const auto& shuttles = repo.getShuttles();

	std::vector<Route> activeRoutes;
	for (const auto& s : shuttles) {
		activeRoutes.push_back(Route(s.get()));
	}
	for (const auto& p : passengers) {
		if (p->getIsAssigned()) continue;

		int pTime = parseTimeStr(p->getTimeStr());
		for (auto& route : activeRoutes) {
			Shuttle* s = route.getShuttle();

			if (p->getDest() == s->getDest()) {
				int sTime = parseTimeStr(s->getTimeStr());


				if (sTime>=(pTime-10) && sTime <= pTime){
					if (route.getCurrentOccupancy() + p->getGroupSize() <= s->getCapacity()) {
						route.addPassenger(p.get());
						p->setAssigned(true);
						break;
				}
				}
			}

		}
	}
}
for (const auto& route : activeRoutes) {
	if (!route.getPassengers().empty()) {
		route.getShuttle()->setAssigned(true);
		repo.addRoute(route);
	}
}