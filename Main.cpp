#include "SchedRepo.h"
#include "SchedGenerator.h"
#include "UIControl.h"
#include "FileParser.h"
#include <iostream>

/*
 * ============================================================================
 * File: Main.cpp
 * Author: Izz Faris Putra Bin Maskhurin
 * Description: Application entry point. Initializes the core system components,
 * passes dependencies, and triggers the UI control loop.
 * ============================================================================
 */


 /*
  * Function: main
  * Author: Izz Faris Putra Bin Maskhurin
  * Description: Application entry point. Instantiates core dependencies (Repo, Generator, FileParser) and injects them into the UI loop. Time Complexity: O(1) setup.
  * Parameters: None
  * Returns: int (exit status)
  */
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