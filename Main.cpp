#include "ScheduleRepository.h"
#include "ScheduleGenerator.h"
#include "UIController.h"
#include "FileParser.h"

int main() {
    // 1. Initialize our decoupled components
    ScheduleRepository repo;
    ScheduleGenerator generator;
    UIController* ui = UIController::getInstance(); // Singleton call

    // 2. Load Data (Using your dedicated FileParser)
    FileParser::loadShuttles("shuttle.txt", repo);
    FileParser::loadPassengers("passenger.txt", repo);

    // 3. Generate matches
    generator.generateMatches(repo);

    // 4. Pass the database to the UI to display
    ui->displayMatches(repo);

    return 0;
}