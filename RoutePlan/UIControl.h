#pragma once
#include "SchedRepo.h"
#include "SchedGenerator.h"

class UIControl {
private:
    UIControl() = default;

public:
    UIControl(const UIControl&) = delete;
    void operator=(const UIControl&) = delete;

    static UIControl& getInstance();

    void startMenu(SchedRepo& repo, SchedGenerator& generator);

    void displayMatches(const SchedRepo& repo) const;
};