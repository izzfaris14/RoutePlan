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
		std::string id, dest, timeStr, type;

		std::getline(ss, id, ',');
		std::getline(ss, dest, ',');
		std::getline(ss, timeStr, ',');
		std::getline(ss, type, ',');

		repo.addShuttle(std::make_unique<Shuttle>(id, dest, timeStr));
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
		std::getline(ss, name, ',');
		std::getline(ss, dest, ',');
		std::getline(ss, timeStr, ',');

		// Default to 1 if partySize is empty

		int size = partySize.empty() ? 1 : std::stoi(partySize); 

		repo.addPassenger(std::make_unique<Passenger>(id, name, dest, timeStr,size));
	}
	file.close();
}

