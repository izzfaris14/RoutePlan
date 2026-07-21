#pragma once
#include <string>
#include <memory>
#include "SchedRepo.h"
#include "Shuttle.h"
#include "Passenger.h"

class FileParser {
private:
    std::unique_ptr<Shuttle> createShuttle(const std::string& id, const std::string& dest, const std::string& timeStr, int cap);
    std::unique_ptr<Passenger> createPassenger(const std::string& id, const std::string& dest, const std::string& timeStr, int size);

public:
    void loadShuttles(const std::string& filename, SchedRepo& repo);
    void loadPassengers(const std::string& filename, SchedRepo& repo);
};