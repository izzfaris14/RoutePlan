#pragma once
#include "SchedRepo.h"
#include <string>

class SchedGenerator {
	int parseTimeStr(const std::string& timeStr) const;
public:
	void generateMatches(SchedRepo& repo);
};
