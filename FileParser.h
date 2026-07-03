#pragma once
#include <string>
#include <vector>
#include "Passenger.h"
#include "Shuttle.h"
#include "SchedRepo.h"

class FileParser {
public:
	static void loadShuttles(const std::string& filename, SchedRepo& repo);
	static void loadPassengers(const std::string& filename, SchedRepo& repo);
};