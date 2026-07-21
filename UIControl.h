#pragma once
#include "SchedRepo.h"
#include "SchedGenerator.h"

/*
 * ============================================================================
 * Class: UIControl
 * Author: Farid Abqary Bin Zainuddin
 * Description: Manages the interactive command-line interface, user prompts,
 * and overarching menu loops.
 * ============================================================================
 */

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