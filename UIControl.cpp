#include "UIControl.h"
#include "Route.h"
#include "SchedRepo.h"
#include <iostream>

UIControl* UIControl::instance = nullptr;

UIControl* UIControl::getInstance() {
	if (instance == nullptr) {
		instance = new UIControl();
	}
	return instance;
}

void UIControl::displayMatches(const SchedRepo& repo) {
	std::cout << "\n===GENERATED ROUTES ===\n" << std::endl;

	const auto& routes = repo.getRoutes();

	if (routes.empty()) {
		std::cout << "no mathces found" << std::endl;
	}
	else {
		for (const auto& r : routes) {
			std::cout << "----" << std::endl;
			std::cout << r.getRouteString() << std::endl;
		}
	}
	std::cout << "====\n" << std::endl;
}