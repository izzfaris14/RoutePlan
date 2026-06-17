#include <iostream>
#include <vector>
#include "FileParser.h"
#include "ShuttleList.h"
#include "PassList.h"
#include "RoutePlanner.h"

using namespace std;

int main() {
    FileParser parser;
    cout << "Loading System Data from files..." << endl;

    vector<Shuttle*> rawShuttles = parser.readShuttles("shuttle.txt");
    vector<Passenger*> rawPassengers = parser.readPassengers("passenger.txt");

    ShuttleList sList(rawShuttles);
    PassList pList(rawPassengers);
    RoutePlanner planner(sList, pList);

    int choice = 0;
    // Updated the loop condition to 8 since we added two new options
    while (choice != 8) {
        cout << "\n==========================================" << endl;
        cout << "  DRIVERLESS PUBLIC TRANSPORT SYSTEM  " << endl;
        cout << "==========================================" << endl;
        cout << "1. Generate Route Matches" << endl;
        cout << "2. Display Detailed Schedule" << endl;
        cout << "3. Display Unmatched Shuttles & Passengers" << endl;
        cout << "4. Add New Entity" << endl;       // NEW
        cout << "5. Delete Entity" << endl;        // NEW
        cout << "6. Edit Parameters in RAM" << endl;
        cout << "7. Save Schedule to File" << endl;
        cout << "8. Exit System" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (choice == 1) {
            planner.generateMatches();
        }
        else if (choice == 2) {
            planner.displayMatches();
        }
        else if (choice == 3) {
            planner.displayUnmatched();
        }
        // --- NEW ADD FUNCTIONALITY ---
        else if (choice == 4) {
            int type;
            string id, dest, time;
            cout << "\nAdd (1) Shuttle or (2) Passenger? ";
            cin >> type;
            cout << "Enter ID: "; cin >> id;
            cout << "Enter Destination: "; cin >> dest;
            cout << "Enter Time (e.g., 8:00am): "; cin >> time;

            if (type == 1) planner.addShuttle(id, dest, time);
            else if (type == 2) planner.addPassenger(id, dest, time);
            else cout << "Invalid choice.\n";
        }
        // --- NEW DELETE FUNCTIONALITY ---
        else if (choice == 5) {
            int type;
            string id;
            cout << "\nDelete (1) Shuttle or (2) Passenger? ";
            cin >> type;
            cout << "Enter ID to delete: "; cin >> id;

            if (type == 1) planner.deleteShuttle(id);
            else if (type == 2) planner.deletePassenger(id);
            else cout << "Invalid choice.\n";
        }
        // --- SHIFTED EDIT FUNCTIONALITY ---
        else if (choice == 6) {
            int editChoice;
            string id, dest, time;
            cout << "\n1. Edit Shuttle\n2. Edit Passenger\nChoice: ";
            cin >> editChoice;

            cout << "Enter ID to replace: "; cin >> id;
            cout << "Enter New Destination: "; cin >> dest;
            cout << "Enter New Time: "; cin >> time;

            if (editChoice == 1) {
                planner.editShuttle(id, dest, time);
            }
            else if (editChoice == 2) {
                planner.editPassenger(id, dest, time);
            }
            else {
                cout << "Invalid edit choice." << endl;
            }
        }
        // --- SHIFTED SAVE FUNCTIONALITY ---
        else if (choice == 7) {
            planner.writeFile("final_schedule.txt");
        }
        // --- SHIFTED EXIT FUNCTIONALITY ---
        else if (choice == 8) {
            cout << "Exiting system..." << endl;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}