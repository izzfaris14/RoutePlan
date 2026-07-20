#include "UIControl.h"
#include "Route.h"
#include "SchedRepo.h"
#include <iostream>

using namespace std;

UIControl* UIControl::instance = nullptr;

UIControl* UIControl::getInstance() {
	if (instance == nullptr) {
		instance = new UIControl();
	}
	return instance;
}

void UIControl::displayMatches(const SchedRepo& repo) {
	cout << "\n===System Scheduling Matches ===\n" << endl;
	if (repo.getRouteCount() == 0) {
		cout << "no matches found.\n";
		return;
	}

	for (size_t i = 0; i < repo.getRouteCount(); i++) {
		const Route& r = repo.getRoute(i);
		cout << r.getRouteString() << "\n";
	}
	cout << "----------\n";
}
	