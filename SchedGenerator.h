#pragma once
#include "SchedRepo.h"
#include <string>

class SchedGenerator {
private:
   
    int parseTimeStr(const std::string& timeStr) const;

public:
    // added algorithm parameter: 
    // 1 = Minimum Shuttle Dispatch (Capacity descending)
    // 2 = Passenger Arrival Time (Time ascending)
    void generateMatches(SchedRepo& repo, int algorithmMode);
};