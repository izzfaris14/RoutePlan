#include "UIControl.h"
#include<iostream>


//initialize the static instance pointer to null
UIControl* UIControl::instance = nullptr; 

UIControl* UIControl::getInstance() {
	if (instance == nullptr) {
		instance = new UIControl();
	}
	return instance;
}

void UIControl::displayMatches(const SchedRepo& repo) {
	cout << "\n=== GENERATED ROUTES ===\n" << endl;

	const auto& routes = repo.getRoutes();

	if (routes.empty()) {
		cout << "no matches found" << endl;
	} else{
		for (const auto& r : routes) {
			cout << "matched established" << endl;
		}
	}
	cout << "=================\n" << endl;
}