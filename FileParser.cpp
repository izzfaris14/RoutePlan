#include "FileParser.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

vector<Passenger*> FileParser::readPassengers(string fileName) {
    vector<Passenger*> passengers;
    ifstream file(fileName);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.empty()) continue; // Skip any accidental blank lines

            stringstream ss(line);
            string id, dest, timeStr;

            // Extract data separated by commas
            getline(ss, id, ',');
            getline(ss, dest, ',');
            getline(ss, timeStr, ',');

            // Create a new pointer and add it to the list
            passengers.push_back(new Passenger(id, dest, timeStr));
        }
        file.close();
    }
    else {
        cout << "Error: Could not open passenger file: " << fileName << endl;
    }

    return passengers;
}

vector<Shuttle*> FileParser::readShuttles(string fileName) {
    vector<Shuttle*> shuttles;
    ifstream file(fileName);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string id, dest, timeStr;

            // Extract data separated by commas
            getline(ss, id, ',');
            getline(ss, dest, ',');
            getline(ss, timeStr, ',');

            // Create a new pointer and add it to the list
            shuttles.push_back(new Shuttle(id, dest, timeStr));
        }
        file.close();
    }
    else {
        cout << "Error: Could not open shuttle file: " << fileName << endl;
    }

    return shuttles;
}