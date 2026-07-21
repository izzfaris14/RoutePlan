#pragma once
#include <string>

/*
 * ============================================================================
 * Class: UIControl
 * Author: Farid Abqary Bin Zainuddin
 * Description: Manages the interactive command-line interface, user prompts,
 * and overarching menu loops.
 * ============================================================================
 */

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
