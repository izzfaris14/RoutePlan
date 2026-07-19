#include "FileParser.h"
#include "Shuttle.h"
#include "Passenger.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

void FileParser::loadShuttles(const std::string& filename, SchedRepo& repo) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string id, dest, timeStr, capacityStr;

		std::getline(ss, id, ',');
		std::getline(ss, dest, ',');
		std::getline(ss, timeStr, ',');
		std::getline(ss, capacityStr, ',');

		// Remove invisible carriage returns (\r) from Windows text files
		if (!capacityStr.empty() && capacityStr.back() == '\r') {
			capacityStr.pop_back();
		}

		// Part 2 Spec: Map "Small", "Family", "Premium" to actual integer capacities
		int capacity = 0;
		if (capacityStr == "Small") capacity = 4;
		else if (capacityStr == "Family") capacity = 7;
		else if (capacityStr == "Premium") capacity = 15;
		else if (!capacityStr.empty()) {
			try { capacity = std::stoi(capacityStr); }
			catch (...) { capacity = 4; } // Default fallback
		}
		else {
			capacity = 4; // Default if column is completely missing
		}

		repo.addShuttle(std::make_unique<Shuttle>(id, dest, timeStr, capacity));
	}
	file.close();
}

void FileParser::loadPassengers(const std::string& filename, SchedRepo& repo) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string id, dest, timeStr, sizeStr;

		std::getline(ss, id, ',');
		std::getline(ss, dest, ',');
		std::getline(ss, timeStr, ',');
		std::getline(ss, sizeStr, ',');

		int partySize = sizeStr.empty() ? 1 : std::stoi(sizeStr);
		repo.addPassenger(std::make_unique<Passenger>(id, dest, timeStr, partySize));
	}
	file.close();
}