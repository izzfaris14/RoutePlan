#include "SchedRepo.h"
#include "SchedGenerator.h"
#include "UIControl.h"
#include "FileParser.h"
#include <iostream>

using namespace std;

int main() {
    // 1. Initialize our decoupled architecture
    //test
    SchedRepo repo;
    SchedGenerator generator;
    UIControl* ui = UIControl::getInstance();

    cout << "System initializing. Loading data from text files..." << endl;

    // 2. Load the Data!
    FileParser::loadShuttles("shuttle.txt", repo);
    FileParser::loadPassengers("passenger.txt", repo);

    cout << "Data loaded successfully. Running scheduling algorithm..." << endl;

    // 3. Generate matches
    generator.generateMatches(repo);

    // 4. Pass the database to the UI to display
    ui->displayMatches(repo);

    return 0;
}