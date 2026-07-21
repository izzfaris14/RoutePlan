#include "SchedRepo.h"
#include "SchedGenerator.h"
#include"UIControl.h"
#include "FileParser.h"
#include<iostream>
#include <string>
#include<fstream>
#include<memory>

using namespace std;


int main() {
	//initialize system
	SchedRepo repo;
	SchedGenerator generator;
	FileParser parser;
	UIControl* ui = UIControl::getInstance();

	cout << "System initializaing...\n";

	//load data and generate initial matched
	parser.loadShuttles("shuttle.txt", repo);
	parser.loadPassengers("passenger.txt", repo);
	generator.generateMatches(repo);

	//interactive menu

	bool running = true;
	int choice = 0;

	while (running) {
		cout << "\n=========================================\n";
		cout << "   Driverless Transport System Menu      \n";
		cout << "=========================================\n";
		cout << "1. Display Found Matches\n";
		cout << "2. Add a New Passenger\n";
		cout << "3. Save Schedule to File\n";
		cout << "4. Exit\n";
		cout << "=========================================\n";
		cout << "Enter your choice (1-4): ";

		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "invalid input. please enter the correct option.\n";
			continue;
		}

		switch (choice) {
		case 1:
			ui->displayMatches(repo);
			break;

		case 2: {
			cout << "\n---Add new Passenger---\n";
			string id, dest, timeStr;
			int gSize;

			cout << "Enter P.ID: ";
			cin >> id;
			cout << "Enter Dest: ";
			cin >> dest;
			cout << "Enter time: ";
			cin >> timeStr;
			cout << "Enter group size: ";
			cin >> gSize;

			//push to RAM
			repo.addPassenger(make_unique<Passenger>(id, dest, timeStr, gSize));

			//re-run the matching algorithm to update the schedule
			repo.clearRoutes();//prevent duplicate
			generator.generateMatches(repo);

			cout << "\nPassenger successfully added and schedule has been updated\n";
			break;
		}
		case 3: {
			cout << "\n---Saving Scheduel---\n";
			ofstream outFile("final_schedule.txt");

			if (outFile.is_open()) {
				//loop through encapsulated data
				for (size_t i = 0; i < repo.getRouteCount(); i++) {
					outFile << repo.getRoute(i).getRouteString() << "\n";
				}
				outFile.close();
				cout << "Schedule successfull saved to final_scehdule.txt\n";
			}
			else {
				cout << "error, could not open file for writing\n";
			}
			break;
		}
		case 4:
			cout << "exiting system. goodbye\n";
			running = false;
			break;

		default:
			cout << "\ninvalide choice. please select 1-4\n";
			break;
		}
	}
	return 0;
}
