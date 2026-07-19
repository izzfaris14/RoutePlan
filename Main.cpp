#include "SchedRepo.h"
#include "SchedGenerator.h"
#include "UIControl.h"
#include "FileParser.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    // 1. Initialize System
    SchedRepo repo;
    SchedGenerator generator;
    FileParser parser;
    UIControl* ui = UIControl::getInstance();

    cout << "System initializing...\n";

    // 2. Load Data & Generate Initial Matches
    parser.loadShuttles("shuttle.txt", repo);
    parser.loadPassengers("passenger.txt", repo);
    generator.generateMatches(repo);

    // 3. Interactive Menu Loop
    bool running = true;
    int choice = 0;

    while (running) {
        cout << "\n=========================================\n";
        cout << "   Driverless Transport System Menu      \n";
        cout << "=========================================\n";
        cout << "1. Display Schedule Matches\n";
        cout << "2. Add a New Passenger\n";
        cout << "3. Save Schedule to File\n";
        cout << "4. Exit\n";
        cout << "=========================================\n";
        cout << "Enter your choice (1-4): ";

        // Input validation to prevent infinite loops if a user types a letter
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            ui->displayMatches(repo);
            break;
        case 2:
            cout << "\n[Feature coming soon: Add Passenger]\n";
            // TODO: Implement std::cin prompts to create a new passenger
            break;
        case 3:
            cout << "\n[Feature coming soon: Save to File]\n";
            // TODO: Implement std::ofstream to save the schedule
            break;
        case 4:
            cout << "\nExiting System. Goodbye!\n";
            running = false;
            break;
        default:
            cout << "\nInvalid choice. Please select 1-4.\n";
            break;
        }
    }

    return 0;
}