#pragma once
#include "Entity.h"

/*
 * ============================================================================
 * Class: Passenger
 * Author: Izz Faris Putra Bin Maskhurin
 * Description: Derived from Entity. Represents a passenger group requesting
 * transit to a specific destination at a specific time.
 * ============================================================================
 */

class Passenger : public Entity {
private:
    int gSize;

public:
    Passenger(const std::string& id, const std::string& dest, const std::string& timeStr, int gSize);

    int getGroupSize() const;
    std::string getDeets() const override;
    bool isAvailable() const override;
    int getCapacity() const override;
};