#include "ScheduleGenerator.h"

void ScheduleGenerator::generateMatches(ScheduleRepository& repo) {
	const auto& passengers = repo.getPassengers();
	const auto& shuttles = repo.getShuttles();

	for (const auto& p : passengers) {
		if (p->getIsAssigned()) continue;

		if (p->getDest()) == s->getDest() && p->getTimeStr() == s->getTimeStr()){

			repo.addRoute(Route(s.get(), p.get()));

			p->setAssigned(true);
			s->setAssigned(true);
			break;  // Move to the next passenger after a match is found
		}
	}
}
}