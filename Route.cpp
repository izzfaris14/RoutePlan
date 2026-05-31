#include "Route.h"

Route::Route(Shuttle s, Passenger p) : sManage(s), pManage(p) {}

string Route::checkDest() const {
	//compare smanage.getDest() and pmanage.getDest()
	if (sManage.getDest() == pManage.getDest()) {
		return "Destination matches: " + sManage.getDest();
	} else {
		return "Destination mismatch";
	}
}

time_t Route::checkTime() const {
	//return appropriate time logic
	return sManage.getTime();
}