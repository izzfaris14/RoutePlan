#pragma once
#include <string>
#include "SchedRepo.h"

class FileParser {
public:
	void loadShuttles(const std::string& filename, SchedRepo& repo);
	void loadPassengers(const std::string& filename, SchedRepo& repo);
};