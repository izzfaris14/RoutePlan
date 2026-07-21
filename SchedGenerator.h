#pragma once
#include "SchedRepo.h"
#include <string>

/*
 * ============================================================================
 * Class: SchedGenerator
 * Author: Linus Ong Yong Chun
 * Description: Contains the core business logic and routing algorithm,
 * evaluating time buffers and vehicle capacities to match passengers to shuttles.
 * ============================================================================
 */

class SchedGenerator {
private:
   
    int parseTimeStr(const std::string& timeStr) const;

public:
    void generateMatches(SchedRepo& repo, int algorithmMode);
};