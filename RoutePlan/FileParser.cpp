#include "FileParser.h"
#include "Shuttle.h"
#include "Passenger.h"
#include "ValidService.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <string>

static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (std::string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}


std::unique_ptr<Shuttle> FileParser::createShuttle(const std::string& id, const std::string& dest, const std::string& timeStr, int cap) {
    return std::make_unique<Shuttle>(id, dest, timeStr, cap);
}

std::unique_ptr<Passenger> FileParser::createPassenger(const std::string& id, const std::string& dest, const std::string& timeStr, int size) {
    return std::make_unique<Passenger>(id, dest, timeStr, size);
}

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
        std::string id, dest, timeStr, capStr;

        std::getline(ss, id, ',');
        std::getline(ss, dest, ',');
        std::getline(ss, timeStr, ',');
        std::getline(ss, capStr, ',');

        id = trim(id);
        dest = trim(dest);
        timeStr = trim(timeStr);
        capStr = trim(capStr);

        if (!ValidService::isValidTimeFormat(timeStr) || !ValidService::isValidOperatingHour(timeStr)) {
            std::cerr << "Warning: Shuttle " << id << " rejected. Invalid time format or outside operating hours (" << timeStr << ").\n";
            continue;
        }

        int capacity = ValidService::mapShuttleModelToCapacity(capStr);
        if (capacity == 2 && capStr != "Small" && capStr != "small") { 
             std::cerr << "Warning: Unknown model '" << capStr << "' for ID " << id << ". Defaulting to Small (2 pax).\n";
        }

        repo.addShuttle(createShuttle(id, dest, timeStr, capacity));
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

        id = trim(id);
        dest = trim(dest);
        timeStr = trim(timeStr);
        sizeStr = trim(sizeStr);

        if (!ValidService::isValidTimeFormat(timeStr) || !ValidService::isValidOperatingHour(timeStr)) {
            std::cerr << "Warning: Passenger " << id << " rejected. Invalid time format or outside operating hours (" << timeStr << ").\n";
            continue;
        }

        int partySize = 1;
        if (!sizeStr.empty()) {
            try {
                partySize = std::stoi(sizeStr);
            }
            catch (...) {
                std::cerr << "Warning: Invalid integer for passenger " << id << ". Defaulting to 1.\n";
            }
        }

        int originalSize = partySize;
        partySize = ValidService::capPassengerGroupSize(partySize);
        if (partySize != originalSize) {
             std::cerr << "Warning: Passenger " << id << " group size (" << originalSize << ") invalid or exceeds max. Capping at " << partySize << ".\n";
        }

        repo.addPassenger(createPassenger(id, dest, timeStr, partySize));
    }
    file.close();
}