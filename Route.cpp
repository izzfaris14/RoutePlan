#include "Route.h"


Route::Route(Shuttle* s, Passenger* p) : sManage(s), pManage(p) {}

string Route::checkDest() const {
	if (sManage->getDest() == pManage->getDest()) {
		return"Match";
	}
	return "mismatch";
}

string Route::checkTime() const {
	if (sManage->getTimeStr() == pManage->getTimeStr()) {
		return "Match";
	}
	return "mismatch";
}

string Route::getRouteString() const {
	return "Shuttle: " + sManage->getId() + "\nPassenger: " + pManage->getId();
}

Shuttle* Route::getShuttle() const {
	return sManage;
}

Passenger* Route::getPassenger() const {
	return pManage;
}