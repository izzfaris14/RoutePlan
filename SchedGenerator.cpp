#include "SchedGenerator.h"

void SchedGenerator::generateMatches(SchedRepo& repo) {
	const auto& passengers = repo.getPassengers();
	const auto& shuttles = repo.getShuttles();

	for (const& p : passengers) {
		if (p->getIsAssinged()) continue; //skip if passenger already matched

		for (const auto& s : shuttles) {
			if (s->getIsAssinged()) continue; //skip if shuttle already matched

			if (p->getDest == s->getDest() && p->getTimeStr() == s->getTimeStr()) {

				repo.addRoute(Route(s.get(), p.get());

				p->setIsAssigned(true);
				s->setIsAssigned(true);
				break;
			}
		}
	}
}