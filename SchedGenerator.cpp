#include "SchedGenerator.h"
#include "Route.h"

void SchedGenerator::generateMatches(SchedRepo& repo) {
	const auto& passengers = repo.getPassengers();
	const auto& shuttles = repo.getShuttles();

	for (const auto& p : passengers) {
		if (p->getIsAssigned()) continue; //skip if passenger already matched

		for (const auto& s : shuttles) {
			if (s->getIsAssigned()) continue; //skip if shuttle already matched

			if (p->getDest() == s->getDest() && p->getTimeStr() == s->getTimeStr()) {

				repo.addRoute(Route(s.get(), p.get()));

				p->setAssigned(true);
				s->setAssigned(true);
				break;
			}
		}
	}
}