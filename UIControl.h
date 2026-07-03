#pragma once
#include "SchedRepo.h"
#include <iostream>

class UIControl {
	static UIControl* instance;
	UIControl() {}

public:
	static UIControl* getInstance();

	void displayMatches(const SchedRepo& repo);
};