#include "ValidService.h"
#include <regex>
#include <sstream>

/*
 * ============================================================================
 * Class: ValidService
 * Author: Linus Ong Yong Chun
 * Description: Provides static validation services to ensure data integrity
 * for both user RAM inputs and parsed file strings.
 * ============================================================================
 */


 /*
  * Function: isValidTimeFormat
  * Author: Linus Ong Yong Chun
  * Description: Uses Regex to ensure a time string strictly matches the hh:mm(am/pm) format. Time Complexity: O(1)
  * Parameters: timeStr (string)
  * Returns: bool (true if valid)
  */
bool ValidService::isValidTimeFormat(const std::string& timeStr) {
    static const std::regex timePattern("^(0?[1-9]|1[0-2]):[0-5][0-9](am|pm)$", std::regex_constants::icase);
    return std::regex_match(timeStr, timePattern);
}


/*
 * Function: isValidOperatingHour
 * Author: Linus Ong Yong Chun
 * Description: Validates that the input time falls within the 6:00am to 00:00am daily operating window. Time Complexity: O(1)
 * Parameters: timeStr (string)
 * Returns: bool
 */
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
/*
 * Function: capPassengerGroupSize
 * Author: Linus Ong Yong Chun
 * Description: Enforces the business rule capping maximum passenger group size to 15. Time Complexity: O(1)
 * Parameters: groupSize (int)
 * Returns: int (capped size)
 */
int ValidService::capPassengerGroupSize(int groupSize) {
    if (groupSize > 15) {
        return 15;
    }
    if (groupSize < 1) {
        return 1;
    }
    return groupSize;
}


/*
 * Function: mapShuttleModelToCapacity (and mapCapacityToShuttleModel)
 * Author: Linus Ong Yong Chun
 * Description: Translates text-based shuttle models (Family, Premium) to numerical seating capacities for the algorithm. Time Complexity: O(1)
 * Parameters: model (string) or capacity (int)
 * Returns: int or string
 */
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
