#pragma once
#include "SchedRepo.h"
#include <string>

class SchedGenerator {
private:
   
    int parseTimeStr(const std::string& timeStr) const;

public:
    void generateMatches(SchedRepo& repo, int algorithmMode);
};