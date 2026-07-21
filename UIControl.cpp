#include "UIControl.h"
#include <iostream>
#include <string>
#include <fstream>

// Thread-safe and memory-safe Singleton instance
UIControl& UIControl::getInstance() {
    static UIControl instance;
    return instance;
}

void UIControl::displayMatches(const SchedRepo& repo) const {
    std::cout << "\n=== System Scheduling Matches ===\n";
    if (repo.getRouteCount() == 0) {
        std::cout << "No matches found. Please run a scheduling algorithm.\n";
        return;
    }

    for (size_t i = 0; i < repo.getRouteCount(); i++) {
        std::cout << repo.getRoute(i).getRouteString() << "\n";
    }
    std::cout << "---------------------------------\n";
}

void UIControl::startMenu(SchedRepo& repo, SchedGenerator& generator) {
    bool running = true;
    int choice = 0;

    while (running) {
        std::cout << "\n=========================================\n";
        std::cout << "   Driverless Transport System Menu      \n";
        std::cout << "=========================================\n";
        std::cout << "1. Generate by Minimum Shuttle Dispatch\n"; 
        std::cout << "2. Generate by Passenger Arrival Time\n";   
        std::cout << "3. Display Current Matches\n";
        std::cout << "4. Add/Edit/Delete Passenger\n";       
        std::cout << "5. Add/Edit/Delete Shuttle\n";           
        std::cout << "6. Save Route Plan to Text File\n";    
        std::cout << "7. Save Entity Data to Text Files\n";  
        std::cout << "8. Display All Entities\n";
        std::cout << "9. Exit\n";
        std::cout << "=========================================\n";
        std::cout << "Enter your choice (1-9): ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            std::cout << "\nRunning Minimum Shuttle Dispatch Algorithm...\n";
            generator.generateMatches(repo, 1);
            displayMatches(repo);
            break;

        case 2:
            std::cout << "\nRunning Passenger Arrival Time Algorithm...\n";
            generator.generateMatches(repo, 2);
            displayMatches(repo);
            break;

        case 3:
            displayMatches(repo);
            break;

        case 4: {
            std::cout << "\n--- Passenger Management ---\n";
            std::cout << "Enter Action (A=Add, E=Edit, D=Delete): ";
            char action;
            std::cin >> action;

            std::string id, dest, timeStr;
            int gSize;

            if (action == 'A' || action == 'a') {
                std::cout << "Enter P.ID: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                std::cout << "Enter Dest: ";
                std::getline(std::cin, dest);
                std::cout << "Enter time: ";
                std::cin >> timeStr;
                std::cout << "Enter group size (Max 15): ";
                std::cin >> gSize;

                if (gSize > 15) {
                    std::cout << "Warning: Group size (" << gSize << ") exceeds standard maximum capacity of 15.\n";
                    std::cout << "Do you still want to add this passenger? (Y/N): ";
                    char confirm;
                    std::cin >> confirm;
                    if (confirm != 'Y' && confirm != 'y') {
                        std::cout << "Operation cancelled. Passenger not added.\n";
                        break;
                    }
                    gSize = 15;
                }
                repo.addPassenger(std::make_unique<Passenger>(id, dest, timeStr, gSize));
                repo.clearRoutes();
                std::cout << "Passenger added to RAM.\n";
            }
            else if (action == 'E' || action == 'e') {
                std::cout << "Enter ID of Passenger to Edit: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                std::cout << "Enter New Dest: ";
                std::getline(std::cin >> std::ws, dest);
                std::cout << "Enter New Time: ";
                std::cin >> timeStr;
                std::cout << "Enter New Group Size: ";
                std::cin >> gSize;

                if (gSize > 15) {
					std::cout << "Warning: Group size (" << gSize << ") exceeds standard maximum capacity of 15.\n";
					std::cout << "Do you still want to edit this passenger? (Y/N): ";
					char confirm;
					std::cin >> confirm;
					if (confirm != 'Y' && confirm != 'y') {
						std::cout << "Operation cancelled. Passenger not edited.\n";
						break;
					}
                    gSize = 15;
                }
                if (repo.editPassenger(id, dest, timeStr, gSize)) {
                    std::cout << "Passenger updated successfully.\n";
                }
                else {
                    std::cout << "Error: Passenger ID not found.\n";
                }
            }
            else if (action == 'D' || action == 'd') {
                std::cout << "Enter ID of Passenger to Delete: ";
                std::cin >> id;
                if (repo.removePassenger(id)) {
                    std::cout << "Passenger deleted successfully.\n";
                }
                else {
                    std::cout << "Error: Passenger ID not found.\n";
                }
            }
            break;
        }

        case 5: {
            std::cout << "\n--- Shuttle Management ---\n";
            std::cout << "Enter Action (A=Add, E=Edit, D=Delete): ";
            char action;
            std::cin >> action;

            std::string id, dest, timeStr, capStr;
            int cap = 2; // Default Small

            if (action == 'A' || action == 'a') {
                std::cout << "Enter S.ID: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                std::cout << "Enter Charging Point: ";
                std::getline(std::cin >> std::ws, dest);
                std::cout << "Enter time: ";
                std::cin >> timeStr;
                std::cout << "Enter Model (Small/Family/Premium): ";
                std::cin >> capStr;

                if (capStr == "Small") cap = 2;
                else if (capStr == "Family") cap = 5;
                else if (capStr == "Premium") cap = 12;
                else cap = 2;

                repo.addShuttle(std::make_unique<Shuttle>(id, dest, timeStr, cap));
                repo.clearRoutes();
                std::cout << "Shuttle added to RAM.\n";
            }
            else if (action == 'E' || action == 'e') {
                std::cout << "Enter ID of Shuttle to Edit: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
                std::cout << "Enter New Charging Point: ";
                std::getline(std::cin >> std::ws, dest);
                std::cout << "Enter New Time: ";
                std::cin >> timeStr;
                std::cout << "Enter New Model (Small/Family/Premium): ";
                std::cin >> capStr;

                if (capStr == "Small") cap = 2;
                else if (capStr == "Family") cap = 5;
                else if (capStr == "Premium") cap = 12;
                else cap = 2;

                if (repo.editShuttle(id, dest, timeStr, cap)) {
                    std::cout << "Shuttle updated successfully.\n";
                }
                else {
                    std::cout << "Error: Shuttle ID not found.\n";
                }
            }
            else if (action == 'D' || action == 'd') {
                std::cout << "Enter ID of Shuttle to Delete: ";
                std::cin >> id;
                if (repo.removeShuttle(id)) {
                    std::cout << "Shuttle deleted successfully.\n";
                }
                else {
                    std::cout << "Error: Shuttle ID not found.\n";
                }
            }
            break;
        }

        case 6: {
            std::cout << "\n--- Saving Schedule ---\n";
            std::ofstream outFile("matched_routes_output.txt");
            if (outFile.is_open()) {
                for (size_t i = 0; i < repo.getRouteCount(); i++) {
                    outFile << repo.getRoute(i).getRouteString() << "\n";
                }
                outFile.close();
                std::cout << "Schedule successfully saved to matched_routes_output.txt\n";
            }
            else {
                std::cout << "Error: Could not open file for writing.\n";
            }
            break;
        }

        case 7: {
            std::cout << "\n--- Saving Entity Data ---\n";

            // Save Passengers
            std::ofstream pFile("new_passengers.txt");
            if (pFile.is_open()) {
                for (size_t i = 0; i < repo.getPassengerCount(); i++) {
                    Passenger* p = repo.getPassenger(i);
                    pFile << p->getId() << ", " << p->getDest() << ", "
                        << p->getTimeStr() << ", " << p->getGroupSize() << "\n";
                }
                pFile.close();
                std::cout << "Passengers saved to new_passengers.txt\n";
            }
            else {
                std::cout << "Error: Could not write to new_passengers.txt\n";
            }

            // Save Shuttles
            std::ofstream sFile("new_shuttles.txt");
            if (sFile.is_open()) {
                for (size_t i = 0; i < repo.getShuttleCount(); i++) {
                    Shuttle* s = repo.getShuttle(i);

                    // Reverse map the integer capacity back to the String model name
                    std::string capStr = "Small";
                    if (s->getCapacity() == 5) capStr = "Family";
                    else if (s->getCapacity() == 12) capStr = "Premium";

                    sFile << s->getId() << ", " << s->getDest() << ", "
                        << s->getTimeStr() << ", " << capStr << "\n";
                }
                sFile.close();
                std::cout << "Shuttles saved to new_shuttles.txt\n";
            }
            else {
                std::cout << "Error: Could not write to new_shuttles.txt\n";
            }
            break;
        }

        case 8:

            std::cout << "Displaying all entities in RAM.\n";
            std::cout << "--- Shuttles ---\n";
            for (size_t i = 0; i < repo.getShuttleCount(); i++) {
                std::cout << repo.getShuttle(i)->getDeets() << "\n";
            }
            std::cout << "--- Passengers ---\n";
            for (size_t i = 0; i < repo.getPassengerCount(); i++) {
                std::cout << repo.getPassenger(i)->getDeets() << "\n";
            }
            break;

		case 9:
            std::cout << "Exiting system. Goodbye.\n";
            running = false;
            break;


        default:
            std::cout << "\nInvalid choice. Please select 1-9.\n";
            break;
        }
    }
}