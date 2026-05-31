//combined PassList & ShuttleList

#include<iostream>
#include "ShuttleList.h"
#include "PassList.h"
#include <fstream>
#include <sstream>

using namespace std;

//helper function to convert time to string
time_t parseTimeStr(const string& timeStr) {
	return time(nullptr); //returning time as a placeholder, implement actual parsing logic as needed
}

void ShuttleList::loadFromFile(string fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		cerr << "Error opening file: " << fileName << endl;
		return;
	}
	string line, id, dest, timeStr;
	while (getline(file, line)) {
		stringstream ss(line);

		getline(ss, id, ','); //read time
		getline(ss, dest, ','); //read destination
		getline(ss, timeStr, ',');//read time
	}

	if (!id.empty() && !dest.empty()) {
		shuttleFile.push_back(Shuttle(id, dest, parseTimeStr(timeStr)));
	}
	file.close();
	cout << "Loading shuttle data from file: " << fileName << endl;
}

vector<Shuttle>& ShuttleList::getShuttles() {
	return shuttleFile;
}

void PassList::loadFromFile(string fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		cerr << "Error opening file: " << fileName << endl;
		return;
	}
	string line, id, dest, timeStr;

	while (getline(file, line)) {
		stringstream ss(line);
		getline(ss, id, ',');//read time
		getline(ss, dest, ',');//read destination
		getline(ss, timeStr, ',');//read time

		if (!id.empty() && !dest.empty()) {
			passFile.push_back(Passenger(id, dest, parseTimeStr(timeStr)));
		}
		file.close();
		cout << "Loading passenger data from file: " << fileName << endl;
	}
}

vector<Passenger>& PassList::getPassengers() {
	return passFile;
}