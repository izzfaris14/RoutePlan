#include "UIControl.h"
#include "ValidService.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>

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
                while (true) {
                    std::cout << "Enter Passenger ID (e.g., P1, P25): ";
                    std::cin >> id;
                    if (ValidService::isValidPassengerId(id))
                        break;
                    std::cout << "Invalid Passenger ID! Format must be P followed by numbers only.\n";
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Dest: ";
                std::getline(std::cin, dest);

                while (true) {
                    std::cout << "Enter Time (e.g., 7:20am): ";
                    std::cin >> timeStr;
                    if (ValidService::isValidTimeFormat(timeStr)) {
                        if (ValidService::isValidOperatingHour(timeStr)) {
                            break;
                        }
                        std::cout << "Time is outside of valid operating hours (6:00am to 12:59am).\n";
                    } else {
                        std::cout << "Invalid time format! Use HH:MMam/pm.\n";
                    }
                }

                while (true) {
                    std::cout << "Enter group size (1-15): ";
                    if (std::cin >> gSize) break;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input! Please enter a number.\n";
                }

                int originalSize = gSize;
                gSize = ValidService::capPassengerGroupSize(gSize);

                if (gSize != originalSize) {
                    std::cout << "Warning: Group size (" << originalSize << ") exceeds standard maximum capacity of 15.\n";
                    std::cout << "Do you still want to add this passenger and cap at 15? (Y/N): ";
                    char confirm;
                    std::cin >> confirm;
                    if (confirm != 'Y' && confirm != 'y') {
                        std::cout << "Operation cancelled. Passenger not added.\n";
                        break;
                    }
                }

                repo.addPassenger(std::make_unique<Passenger>(id, dest, timeStr, gSize));
                repo.clearRoutes();
                std::cout << "Passenger added to RAM successfully.\n";
            }
            else if (action == 'E' || action == 'e') {
                std::cout << "Enter ID of Passenger to Edit: ";
                std::cin >> id;
                if (repo.getPassengerById(id) == nullptr) {
                    std::cout << "Error: Passenger ID not found.\n";
                    break;
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Enter New Dest: ";
                std::getline(std::cin >> std::ws, dest);

                while (true) {
                    std::cout << "Enter New Time (e.g., 7:20am): ";
                    std::cin >> timeStr;
                    if (ValidService::isValidTimeFormat(timeStr)) {
                        if (ValidService::isValidOperatingHour(timeStr)) {
                            break;
                        }
                        std::cout << "Time is outside of valid operating hours (6:00am to 12:59am).\n";
                    } else {
                        std::cout << "Invalid time format! Use HH:MMam/pm.\n";
                    }
                }
                
                while (true) {
                    std::cout << "Enter New Group Size (1-15): ";
                    if (std::cin >> gSize) break;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input! Please enter a number.\n";
                }

                int originalSize = gSize;
                gSize = ValidService::capPassengerGroupSize(gSize);

                if (gSize != originalSize) {
					std::cout << "Warning: Group size (" << originalSize << ") exceeds standard maximum capacity of 15.\n";
					std::cout << "Do you still want to edit this passenger and cap at 15? (Y/N): ";
					char confirm;
					std::cin >> confirm;
					if (confirm != 'Y' && confirm != 'y') {
						std::cout << "Operation cancelled. Passenger not edited.\n";
						break;
					}
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

            std::string id, dest, timeStr, modelStr;

            if (action == 'A' || action == 'a') {
                while (true) {
                    std::cout << "Enter Shuttle ID (e.g., S1, S25): ";
                    std::cin >> id;
                    if (ValidService::isValidShuttleId(id))
                        break;
                    std::cout << "Invalid Shuttle ID! Format must be S followed by numbers only.\n";
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Charging Point: ";
                std::getline(std::cin >> std::ws, dest);

                while (true) {
                    std::cout << "Enter Time (e.g., 7:20am): ";
                    std::cin >> timeStr;
                    if (ValidService::isValidTimeFormat(timeStr)) {
                        if (ValidService::isValidOperatingHour(timeStr)) {
                            break;
                        }
                        std::cout << "Time is outside of valid operating hours (6:00am to 12:59am).\n";
                    } else {
                        std::cout << "Invalid time format! Use HH:MMam/pm.\n";
                    }
                }

                std::cout << "Enter Model (Small/Family/Premium): ";
                std::cin >> modelStr;
                int cap = ValidService::mapShuttleModelToCapacity(modelStr);

                repo.addShuttle(std::make_unique<Shuttle>(id, dest, timeStr, cap));
                repo.clearRoutes();
                std::cout << "Shuttle added to RAM.\n";
            }
            else if (action == 'E' || action == 'e') {
                std::cout << "Enter ID of Shuttle to Edit: ";
                std::cin >> id;
                if (repo.getShuttleById(id) == nullptr) {
                    std::cout << "Error: Shuttle ID not found.\n";
                    break;
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Enter New Charging Point: ";
                std::getline(std::cin >> std::ws, dest);

                while (true) {
                    std::cout << "Enter New Time (e.g., 7:20am): ";
                    std::cin >> timeStr;
                    if (ValidService::isValidTimeFormat(timeStr)) {
                        if (ValidService::isValidOperatingHour(timeStr)) {
                            break;
                        }
                        std::cout << "Time is outside of valid operating hours (6:00am to 12:59am).\n";
                    } else {
                        std::cout << "Invalid time format! Use HH:MMam/pm.\n";
                    }
                }

                std::cout << "Enter New Model (Small/Family/Premium): ";
                std::cin >> modelStr;
                int cap = ValidService::mapShuttleModelToCapacity(modelStr);

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

            std::ofstream sFile("new_shuttles.txt");
            if (sFile.is_open()) {
                for (size_t i = 0; i < repo.getShuttleCount(); i++) {
                    Shuttle* s = repo.getShuttle(i);
                    std::string modelStr = ValidService::mapCapacityToShuttleModel(s->getCapacity());
                    sFile << s->getId() << ", " << s->getDest() << ", "
                        << s->getTimeStr() << ", " << modelStr << "\n";
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