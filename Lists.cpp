
#include<iostream>
#include "ShuttleList.h"
#include "PassList.h"
#include <fstream>
#include <sstream>

using namespace std;


string parseTimeStr(const string& timeStr) {
	return timeStr;
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

		getline(ss, id, ',');
		getline(ss, dest, ',');
		getline(ss, timeStr, ',');
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
		getline(ss, id, ',');
		getline(ss, dest, ',');
		getline(ss, timeStr, ',');

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