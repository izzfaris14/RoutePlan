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
		if (line.empty()) continue; // Skip empty lines

		std::stringstream ss(line);
		std::string id, dest, timeStr, CapacityStr;

		std::getline(ss, id, ',');
		std::getline(ss, dest, ',');
		std::getline(ss, timeStr, ',');
		std::getline(ss, CapacityStr, ',');

		if (!CapacityStr.empty() && CapacityStr.back() == '\r') {
			CapacityStr.pop_back();
	}
		int capacity = 0;
		if (CapacityStr == "Small") capacity = 4;
		else if (CapacityStr == "Family") capacity = 7;
		else if (CapacityStr == "Premium") capacity = 15;
		else if (!CapacityStr.empty()) {
			try { capacity = std::stoi(CapacityStr); }
			catch (...) { capacity = 4; }
		}
		else {
			capacity = 4;
		}
		repo.addShuttle(std::make_unique<Shuttle>)(id, dest, timeStr, capacity));
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
		if (line.empty()) continue; // Skip empty lines

		std::stringstream ss(line);
		std::string id, name, dest, timeStr, partySize;

		std::getline(ss, id, ',');
		std::getline(ss, dest, ',');
		std::getline(ss, timeStr, ',');
		std::getline(ss, partySize, ',');

		// Default to 1 if partySize is empty

		int size = partySize.empty() ? 1 : std::stoi(partySize); 

		repo.addPassenger(std::make_unique<Passenger>(id, dest, timeStr,size));
	}
	file.close();
}

