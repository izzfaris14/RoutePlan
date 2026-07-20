#include "SchedGenerator.h"
#include <iostream>

void SchedGenerator::generateMatches(SchedRepo& repo) {
	for (size_t i = 0; i < repo.getShuttleCount(); i++) {
		Shuttle* s = repo.getShuttle(i);

		//skip if fully booked
		if (!s->isAvailable()) continue;

		Route newRoute(s);

		for (size_t j = 0; j < repo.getPassengerCount(); j++) {
			Passenger* p = repo.getPassenger(j);

			if (p->getIsAssigned()) continue;

			//matching logic

			if (p->getDest() == s->getDest() && p->getTimeStr() == s->getTimeStr()) {
				if (s->getCapacity() >= p->getGroupSize()) {
					newRoute.addPassenger(p);
					p->setAssigned(true);
					s->setCapacity(s->getCapacity() - p->getGroupSize());
				}
			}
		}

		if (newRoute.getPassengerCount() > 0) {
			repo.addRoute(newRoute);
			if (s->getCapacity() == 0) {
				s->setAssigned(true);
			}
		}
	}
}