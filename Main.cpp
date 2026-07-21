#include "SchedRepo.h"
#include "SchedGenerator.h"
#include "UIControl.h"
#include "FileParser.h"
#include <iostream>

int main() {
    std::cout << "System Initializing...\n";

    SchedRepo repo;
    SchedGenerator generator;
    FileParser parser;

    // Load initial data files
    parser.loadShuttles("shuttle.txt", repo);
    parser.loadPassengers("passenger.txt", repo);

    // Delegate all user interaction to the UI layer
    UIControl& ui = UIControl::getInstance();
    ui.startMenu(repo, generator);

    return 0;
}