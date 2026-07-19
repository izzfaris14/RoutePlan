#pragma once
#include "SchedRepo.h"

class UIControl {
	static UIControl* instance;
	UIControl() {}
public:
	static UIControl* getInstance();
	void displayMatches(const SchedRepo& repo);
};