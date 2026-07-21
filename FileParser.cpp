#include "FileParser.h"
#include "Shuttle.h"
#include "Passenger.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <string>

// Helper 1: Sanitize inputs by stripping trailing/leading whitespaces
static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (std::string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Helper 2: Enforce the 6:00am to 00:00am daily operating limit
static bool isValidOperatingHour(const std::string& timeStr) {
    if (timeStr.empty() || timeStr.length() < 3) return false;

    int hours = 0;
    std::string period = timeStr.substr(timeStr.length() - 2);

    std::stringstream ss(timeStr.substr(0, timeStr.length() - 2));
    ss >> hours;

    // Reject times between 1:00am and 5:59am
    if (period == "am" && hours < 6 && hours != 12) {
        return false;
    }
    return true;
}


std::unique_ptr<Shuttle> FileParser::createShuttle(const std::string& id, const std::string& dest, const std::string& timeStr, int cap) {
    return std::make_unique<Shuttle>(id, dest, timeStr, cap);
}

std::unique_ptr<Passenger> FileParser::createPassenger(const std::string& id, const std::string& dest, const std::string& timeStr, int size) {
    return std::make_unique<Passenger>(id, dest, timeStr, size);
}
// -------------------------------------------

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

        // Validation: Reject invalid operating hours
        if (!isValidOperatingHour(timeStr)) {
            std::cerr << "Warning: Shuttle " << id << " rejected. " << timeStr << " is outside operating hours.\n";
            continue;
        }

        int capacity = 0;
        if (capStr == "Small") {
            capacity = 2;
        }
        else if (capStr == "Family") {
            capacity = 5;
        }
        else if (capStr == "Premium") {
            capacity = 12;
        }
        else {
            std::cerr << "Warning: Unknown model '" << capStr << "' for ID " << id << ". Defaulting to Small (2 pax).\n";
            capacity = 2;
        }

        // Utilizing the Factory Method
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

        // reject invalid operating hours
        if (!isValidOperatingHour(timeStr)) {
            std::cerr << "Warning: Passenger " << id << " rejected. " << timeStr << " is outside operating hours.\n";
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

        if (partySize > 15) {
            std::cerr << "Warning: Passenger " << id << " exceeds max group size. Capping at 15.\n";
            partySize = 15;
        }
        else if (partySize < 1) {
            partySize = 1;
        }

        // Utilizing the Factory Method
        repo.addPassenger(createPassenger(id, dest, timeStr, partySize));
    }
    file.close();
}