#include "UIControl.h"
#include<iostream>

using namespace std;

//initialize the static instance pointer to nullptr
UIControl* UIControl::instance = nullptr; 

UIControl* UIControl::getInstance() {
	if (instance == nullptr) {
		instance = new UIControl();
	}
	return instance;
}

void UIControl::displayMatches(const SchedRepo& repo) {
	cout << "\n=== GENERATED ROUTES ===\n" << endl;

	if (routes.empty()) {
		cout << "no matches found" << endl;
	} else{
		for (const auto& r : routes) {
			cout << "matched established" << endl;
		}
	}
	cout << "=================\n" << endl;
}