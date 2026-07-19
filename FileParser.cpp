#include "FileParser.h"
#include "Shuttle.h"
#include "Passenger.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include<string>

void FileParser::loadShuttles(const std::string& filename, SchedRepo& repo) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		if (line.empty())continue;

		std::stringstream ss(line);
		std::string id, dest, timeStr, capStr;

		std::getline(ss, id, ',');
		std::getline(ss, dest, ',');
		std::getline(ss, timeStr, ',');
		std::getline(ss, capStr, ',');

		if (!capStr.empty() && capStr.back() == '\r') {
			capStr.pop_back();
		}

		int capacity = 0;
		if (capStr == "Small") capacity = 4;
		else if (capStr == "Family") capacity = 7;
		else if (capStr == "Premium") capacity = 15;
		else if (!capStr.empty()) {
			try {
				capacity = std::stoi(capStr);
			}
			catch (...) { capacity = 4; }
		}
		else {
			capacity = 4;
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
		if (line.empty())continue;

		std::stringstream ss(line);
		std::string id, dest, timeStr, sizeStr;

		std::getline(ss, id, ',');
		std::getline(ss, dest, ',');
		std::getline(ss, timeStr, ',');
		std::getline(ss, sizeStr, ',');

		int partSize = sizeStr.empty() ? 1 : std::stoi(sizeStr);
		repo.addPassenger(std::make_unique<Passenger>(id, dest, timeStr, partyStr));
	}
	file.close();
}





