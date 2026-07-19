#include "SchedRepo.h"
#include "SchedGenerator.h"
#include "UIControl.h"
#include "FileParser.h"
#include <iostream>

using namespace std;

int main() {
    // 1. Initialize our decoupled architecture
    SchedRepo repo;
    SchedGenerator generator;
    FileParser parser;
    UIControl* ui = UIControl::getInstance();

    cout << "System initializing...\n";

    // 2. Load the data using FileParser
    parser.loadShuttles("shuttle.txt", repo);
    parser.loadPassengers("passenger.txt", repo);

    // 3. Generate the matches! (This is what you were missing)
    generator.generateMatches(repo);

    // 4. Display the results
    ui->displayMatches(repo);

    return 0;
}