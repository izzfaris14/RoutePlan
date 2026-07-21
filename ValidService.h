#pragma once
#include <string>

class ValidService {
public:
    // Time validations
    static bool isValidTimeFormat(const std::string& timeStr);
    static bool isValidOperatingHour(const std::string& timeStr);

    // ID validations
    static bool isValidPassengerId(const std::string& id);
    static bool isValidShuttleId(const std::string& id);

    // Entity-specific validations
    static int capPassengerGroupSize(int groupSize);

    // Shuttle model/capacity mapping
    static int mapShuttleModelToCapacity(const std::string& model);
    static std::string mapCapacityToShuttleModel(int capacity);
};
