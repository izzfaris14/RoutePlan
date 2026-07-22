#include "UIControl.h"
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>

/*
 * ============================================================================
 * Class: UIControl
 * Author: Linus Ong Yong Chun
 * Description: Manages the interactive command-line interface, user prompts,
 * and overarching menu loops.
 * ============================================================================
 */

 /*
  * Function: getInstance
  * Author: Linus Ong Yong Chun
  * Description: Thread-safe and memory-safe Singleton access point for the UI controller. Time Complexity: O(1)
  * Parameters: None
  * Returns: UIControl& (Reference to singleton instance)
  */
UIControl& UIControl::getInstance() {
    static UIControl instance;
    return instance;
}

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
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


/*
 * Function: startMenu
 * Author: Linus Ong Yong Chun
 * Description: The primary interactive terminal loop allowing users to trigger scheduling, edit RAM entities, and save data. Time Complexity: O(N) per user action.
 * Parameters: repo (SchedRepo&), generator (SchedGenerator&)
 * Returns: void
 */
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
        std::cout << "8. View All Passengers & Shuttles (RAM)\n";
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
                // Validate Passenger ID format (Must start with P)
                while (true) {
                    std::cout << "Enter P.ID (Must start with 'P', e.g., P01): ";
                    std::cin >> id;
                    id = trim(id);
                    if (id.length() >= 2 && (id[0] == 'P' || id[0] == 'p')) break;
                    std::cout << "Invalid ID format! Passenger ID must start with 'P'.\n";
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Dest: ";
                std::getline(std::cin, dest);
                dest = trim(dest);

                while (true) {
                    std::cout << "Enter time (e.g., 7:20am or 00:00am): ";
                    std::cin >> timeStr;
                    timeStr = trim(timeStr);

                    bool hasColon = (timeStr.find(':') != std::string::npos);
                    bool hasSuffix = (timeStr.length() >= 3 &&
                        (timeStr.rfind("am") == timeStr.length() - 2 ||
                            timeStr.rfind("pm") == timeStr.length() - 2));

                    bool validTime = false;
                    if (hasColon && hasSuffix) {
                        size_t colonPos = timeStr.find(':');
                        std::string hourPart = timeStr.substr(0, colonPos);
                        // Minutes are everything between the colon and the 2-character suffix (am/pm)
                        std::string minPart = timeStr.substr(colonPos + 1, timeStr.length() - colonPos - 3);

                        // Check if hour and minute strings consist purely of digits
                        auto isDigits = [](const std::string& s) {
                            if (s.empty()) return false;
                            for (char c : s) if (!isdigit(c)) return false;
                            return true;
                            };

                        if (isDigits(hourPart) && isDigits(minPart)) {
                            int h = std::stoi(hourPart);
                            int m = std::stoi(minPart);

                            bool validHour = (h >= 0 && h <= 12); // Accepts 0-12 (with 0/00 or 12 for midnight)
                            bool validMin = (m >= 0 && m <= 59);   // Strictly restricts minutes to 00-59

                            if (validHour && validMin) {
                                validTime = true;
                            }
                        }
                    }

                    if (validTime) break;
                    std::cout << "Invalid time format!.\n";
                }

                while (true) {
                    std::cout << "Enter group size (Numbers only): ";
                    if (std::cin >> gSize && gSize > 0) break;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid group size! Please enter a valid number.\n";
                }

                if (gSize > 15) {
                    std::cout << "Warning: Group size (" << gSize << ") exceeds standard maximum capacity of 15.\n";
                    std::cout << "Do you still want to add this passenger and cap at 15? (Y/N): ";
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
                std::cout << "Passenger added to RAM successfully.\n";
            }
            else if (action == 'E' || action == 'e') {
                std::cout << "Enter ID of Passenger to Edit: ";
                std::cin >> id;
                id = trim(id);

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter New Dest: ";
                std::getline(std::cin, dest);
                dest = trim(dest);

                while (true) {
                    std::cout << "Enter time (e.g., 7:20am or 00:00am): ";
                    std::cin >> timeStr;
                    timeStr = trim(timeStr);

                    bool hasColon = (timeStr.find(':') != std::string::npos);
                    bool hasSuffix = (timeStr.length() >= 3 &&
                        (timeStr.rfind("am") == timeStr.length() - 2 ||
                            timeStr.rfind("pm") == timeStr.length() - 2));

                    bool validTime = false;
                    if (hasColon && hasSuffix) {
                        size_t colonPos = timeStr.find(':');
                        std::string hourPart = timeStr.substr(0, colonPos);
                        // Minutes are everything between the colon and the 2-character suffix (am/pm)
                        std::string minPart = timeStr.substr(colonPos + 1, timeStr.length() - colonPos - 3);

                        // Check if hour and minute strings consist purely of digits
                        auto isDigits = [](const std::string& s) {
                            if (s.empty()) return false;
                            for (char c : s) if (!isdigit(c)) return false;
                            return true;
                            };

                        if (isDigits(hourPart) && isDigits(minPart)) {
                            int h = std::stoi(hourPart);
                            int m = std::stoi(minPart);

                            bool validHour = (h >= 0 && h <= 12); // Accepts 0-12 (with 0/00 or 12 for midnight)
                            bool validMin = (m >= 0 && m <= 59);   // Strictly restricts minutes to 00-59

                            if (validHour && validMin) {
                                validTime = true;
                            }
                        }
                    }

                    if (validTime) break;
                    std::cout << "Invalid time format!.\n";
                }

                while (true) {
                    std::cout << "Enter New Group Size (Numbers only): ";
                    if (std::cin >> gSize && gSize > 0) break;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid group size! Please enter a valid number.\n";
                }

                if (gSize > 15) {
                    std::cout << "Warning: Group size (" << gSize << ") exceeds standard maximum capacity of 15.\n";
                    std::cout << "Do you still want to update and cap at 15? (Y/N): ";
                    char confirm;
                    std::cin >> confirm;
                    if (confirm != 'Y' && confirm != 'y') {
                        std::cout << "Operation cancelled. Passenger not updated.\n";
                        break;
                    }
                    gSize = 15;
                }

                if (repo.editPassenger(id, dest, timeStr, gSize)) {
                    repo.clearRoutes();
                    std::cout << "Passenger updated successfully.\n";
                }
                else {
                    std::cout << "Error: Passenger ID not found.\n";
                }
            }
            else if (action == 'D' || action == 'd') {
                std::cout << "Enter ID of Passenger to Delete: ";
                std::cin >> id;
                id = trim(id);
                if (repo.removePassenger(id)) {
                    repo.clearRoutes();
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
                // Validate Shuttle ID format (Must start with S)
                while (true) {
                    std::cout << "Enter S.ID (Must start with 'S', e.g., S01): ";
                    std::cin >> id;
                    if (id.length() >= 2 && (id[0] == 'S' || id[0] == 's')) break;
                    std::cout << "Invalid ID format! Shuttle ID must start with 'S'.\n";
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Charging Point: ";
                std::getline(std::cin, dest);

                while (true) {
                    std::cout << "Enter time (e.g., 7:20am or 00:00am): ";
                    std::cin >> timeStr;
                    timeStr = trim(timeStr);

                    bool hasColon = (timeStr.find(':') != std::string::npos);
                    bool hasSuffix = (timeStr.length() >= 3 &&
                        (timeStr.rfind("am") == timeStr.length() - 2 ||
                            timeStr.rfind("pm") == timeStr.length() - 2));

                    bool validTime = false;
                    if (hasColon && hasSuffix) {
                        size_t colonPos = timeStr.find(':');
                        std::string hourPart = timeStr.substr(0, colonPos);
                        // Minutes are everything between the colon and the 2-character suffix (am/pm)
                        std::string minPart = timeStr.substr(colonPos + 1, timeStr.length() - colonPos - 3);

                        // Check if hour and minute strings consist purely of digits
                        auto isDigits = [](const std::string& s) {
                            if (s.empty()) return false;
                            for (char c : s) if (!isdigit(c)) return false;
                            return true;
                            };

                        if (isDigits(hourPart) && isDigits(minPart)) {
                            int h = std::stoi(hourPart);
                            int m = std::stoi(minPart);

                            bool validHour = (h >= 0 && h <= 12); // Accepts 0-12 (with 0/00 or 12 for midnight)
                            bool validMin = (m >= 0 && m <= 59);   // Strictly restricts minutes to 00-59

                            if (validHour && validMin) {
                                validTime = true;
                            }
                        }
                    }

                    if (validTime) break;
                    std::cout << "Invalid time format!.\n";
                }
                std::cout << "Enter Model (Small/Family/Premium): ";
                std::cin >> capStr;
                capStr = trim(capStr);

                if (capStr == "Small" || capStr == "small") cap = 2;
                else if (capStr == "Family" || capStr == "family") cap = 5;
                else if (capStr == "Premium" || capStr == "premium") cap = 12;
                else cap = 2;

                repo.addShuttle(std::make_unique<Shuttle>(id, dest, timeStr, cap));
                repo.clearRoutes();
                std::cout << "Shuttle added to RAM.\n";
            }
            else if (action == 'E' || action == 'e') {
                std::cout << "Enter ID of Shuttle to Edit: ";
                std::cin >> id;

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter New Charging Point: ";
                std::getline(std::cin, dest);

                while (true) {
                    std::cout << "Enter time (e.g., 7:20am or 00:00am): ";
                    std::cin >> timeStr;
                    timeStr = trim(timeStr);

                    bool hasColon = (timeStr.find(':') != std::string::npos);
                    bool hasSuffix = (timeStr.length() >= 3 &&
                        (timeStr.rfind("am") == timeStr.length() - 2 ||
                            timeStr.rfind("pm") == timeStr.length() - 2));

                    bool validTime = false;
                    if (hasColon && hasSuffix) {
                        size_t colonPos = timeStr.find(':');
                        std::string hourPart = timeStr.substr(0, colonPos);
                        // Minutes are everything between the colon and the 2-character suffix (am/pm)
                        std::string minPart = timeStr.substr(colonPos + 1, timeStr.length() - colonPos - 3);

                        // Check if hour and minute strings consist purely of digits
                        auto isDigits = [](const std::string& s) {
                            if (s.empty()) return false;
                            for (char c : s) if (!isdigit(c)) return false;
                            return true;
                            };

                        if (isDigits(hourPart) && isDigits(minPart)) {
                            int h = std::stoi(hourPart);
                            int m = std::stoi(minPart);

                            bool validHour = (h >= 0 && h <= 12); // Accepts 0-12 (with 0/00 or 12 for midnight)
                            bool validMin = (m >= 0 && m <= 59);   // Strictly restricts minutes to 00-59

                            if (validHour && validMin) {
                                validTime = true;
                            }
                        }
                    }

                    if (validTime) break;
                    std::cout << "Invalid time format!.\n";
                }

                std::cout << "Enter New Model (Small/Family/Premium): ";
                std::cin >> capStr;
                capStr = trim(capStr);

                if (capStr == "Small" || capStr == "small") cap = 2;
                else if (capStr == "Family" || capStr == "family") cap = 5;
                else if (capStr == "Premium" || capStr == "premium") cap = 12;
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
                id = trim(id);
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
