#pragma once
#include "ScheduleRepo.h"
#include <iostream>

class UIControl {
	static UIControl* instance;

	UIControl() = {}

public:
	static UIControl * getInstance();

	void displayMainMenu();
	void displayMatches(const ScheduleRepo& repo);
	void displayUnmatched(const ScheduleRepo& repo);
	void promptForNewPassenger(ScheduleRepo& repo);
};

