#include "ValidService.h"
#include <regex>
#include <sstream>

/*
 * ============================================================================
 * Class: ValidService
 * Author: Farid Abqary Bin Zainuddin
 * Description: Provides static validation services to ensure data integrity
 * for both user RAM inputs and parsed file strings.
 * ============================================================================
 */

bool ValidService::isValidTimeFormat(const std::string& timeStr) {
    static const std::regex timePattern("^(0?[1-9]|1[0-2]):[0-5][0-9](am|pm)$", std::regex_constants::icase);
    return std::regex_match(timeStr, timePattern);
}

bool ValidService::isValidOperatingHour(const std::string& timeStr) {
    if (timeStr.empty() || timeStr.length() < 3) return false;

    int hours = 0;
    try {
        hours = std::stoi(timeStr.substr(0, timeStr.find(':')));
    } catch (...) {
        return false; 
    }

    std::string period = timeStr.substr(timeStr.length() - 2);
    if(period.length() != 2) return false;
    std::transform(period.begin(), period.end(), period.begin(), ::tolower);


    if (period == "am" && hours >= 1 && hours <= 5) {
        return false;
    }
    return true;
}

bool ValidService::isValidPassengerId(const std::string& id) {
    static const std::regex passengerID("^P[0-9]+$", std::regex_constants::icase);
    return std::regex_match(id, passengerID);
}

bool ValidService::isValidShuttleId(const std::string& id) {
    static const std::regex shuttleID("^S[0-9]+$", std::regex_constants::icase);
    return std::regex_match(id, shuttleID);
}

int ValidService::capPassengerGroupSize(int groupSize) {
    if (groupSize > 15) {
        return 15;
    }
    if (groupSize < 1) {
        return 1;
    }
    return groupSize;
}

int ValidService::mapShuttleModelToCapacity(const std::string& model) {
    std::string lowerModel = model;
    std::transform(lowerModel.begin(), lowerModel.end(), lowerModel.begin(), ::tolower);

    if (lowerModel == "family") return 5;
    if (lowerModel == "premium") return 12;
    return 2;
}

std::string ValidService::mapCapacityToShuttleModel(int capacity) {
    if (capacity == 5) return "Family";
    if (capacity == 12) return "Premium";
    return "Small";
}
