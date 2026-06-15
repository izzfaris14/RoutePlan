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
    vector<Passenger*> rawPassengers = parser.readPassengers("passengers.txt");

    ShuttleList sList(rawShuttles);
    PassList pList(rawPassengers);
    RoutePlanner planner(sList, pList);

    int choice = 0;
    while (choice != 6) {
        cout << "\n==========================================" << endl;
        cout << "  DRIVERLESS PUBLIC TRANSPORT SYSTEM RAM  " << endl;
        cout << "==========================================" << endl;
        cout << "1. Generate Route Matches" << endl;
        cout << "2. Display Detailed Schedule" << endl;
        cout << "3. Display Unmatched Shuttles & Passengers" << endl;
        cout << "4. Save Schedule to File" << endl;
        cout << "5. Edit Entities in RAM" << endl;
        cout << "6. Exit System" << endl;
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
        else if (choice == 4) {
            planner.writeFile("final_schedule.txt");
        }
        else if (choice == 5) {
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
        else if (choice == 6) {
            cout << "Exiting system. Have a good day!" << endl;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}