#pragma once
#include "Entity.h"

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