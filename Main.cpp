#include "SchedRepo.h"
#include "SchedGenerator.h"
#include "UIControl.h"
#include <iostream>

using namespace std;

int main() {
    // 1. Initialize our decoupled architecture
    SchedRepo repo;
    SchedGenerator generator;
    UIControl* ui = UIControl::getInstance(); // Singleton Call

    /* NOTE: You will call your FileParser here.
       Since we upgraded to std::unique_ptr, you'll need to make sure
       your FileParser uses make_unique when creating new entities.

       Example:
       repo.addShuttle(make_unique<Shuttle>("S01", "School", "07:15am"));
    */

    cout << "System initialized. Running scheduling algorithm..." << endl;

    // 2. Generate matches
    generator.generateMatches(repo);

    // 3. Pass the database to the UI to display
    ui->displayMatches(repo);

    return 0;
}