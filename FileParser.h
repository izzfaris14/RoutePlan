#pragma once
#include <string>
#include <memory>
#include "SchedRepo.h"
#include "Shuttle.h"
#include "Passenger.h"

/*
 * ============================================================================
 * Class: FileParser
 * Author: Lex Lee Gao Hao
 * Description: A dedicated utility class responsible for all file I/O operations,
 * string extraction, and protecting the core logic from UI/File dependencies.
 * ============================================================================
 */

class FileParser {
private:
    std::unique_ptr<Shuttle> createShuttle(const std::string& id, const std::string& dest, const std::string& timeStr, int cap);
    std::unique_ptr<Passenger> createPassenger(const std::string& id, const std::string& dest, const std::string& timeStr, int size);

public:
    void loadShuttles(const std::string& filename, SchedRepo& repo);
    void loadPassengers(const std::string& filename, SchedRepo& repo);
};