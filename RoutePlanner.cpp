#include <iostream>
#include <fstream>
#include "RoutePlanner.h"

using namespace std;

RoutePlanner::RoutePlanner(ShuttleList sList, PassList pList) : sManager(sList), pManager(pList) {}

void RoutePlanner::initializeSystem(FileParser& parser) {
}

void RoutePlanner::generateMatches() {
    cout << "Generating matches between shuttles and passengers..." << endl;

    const vector<Passenger*>& passengers = pManager.getPassengers();
    const vector<Shuttle*>& shuttles = sManager.getShuttles();

    for (const auto& p : passengers) {
        for (const auto& s : shuttles) {
           
            if (p->getDest() == s->getDest() && p->getTimeStr() == s->getTimeStr()) {
                matchedRoutes.push_back(Route(s, p));
                break; 
            }
        }
    }
    cout << "Matched " << matchedRoutes.size() << " routes." << endl;
}

void RoutePlanner::editShuttle(string id, string newDest, string newTime) {
    cout << "Editing shuttle in RAM: ID=" << id << ", New Destination=" << newDest << ", New Time=" << newTime << endl;

    Shuttle* updated = new Shuttle(id, newDest, newTime);
    sManager.editShuttle(id, updated);
}

void RoutePlanner::editPassenger(string id, string newDest, string newTime) {
    cout << "Editing passenger in RAM: ID=" << id << ", New Destination=" << newDest << ", New Time=" << newTime << endl;

    Passenger* updated = new Passenger(id, newDest, newTime);
    pManager.editPassenger(id, updated);
}

void RoutePlanner::writeFile(string fileName) {
    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing: " << fileName << endl;
        return;
    }

    outFile << "=== FINAL TRANSIT SCHEDULE ===" << endl;
    for (const auto& route : matchedRoutes) {
       
        outFile << route.getRouteString() << endl;
    }

    outFile.close();
    cout << "Matched routes written to file: " << fileName << endl;
}

void RoutePlanner::displayMatches() const {
    if (matchedRoutes.empty()) {
        cout << "No matches to display. Please generate matches first." << endl;
        return;
    }
    cout << "\n=== DETAILED SCHEDULE ===" << endl;
    for (const auto& route : matchedRoutes) {
        cout << route.getRouteString() << endl;
    }
}

void RoutePlanner::displayUnmatched() const {
    cout << "\n=== UNMATCHED SHUTTLES ===" << endl;
    for (const auto& s : sManager.getShuttles()) {
        bool isMatched = false;
        for (const auto& r : matchedRoutes) {
            if (r.getShuttle()->getId() == s->getId()) {
                isMatched = true;
                break;
            }
        }
        if (!isMatched) cout << s->getDeets() << endl;
    }

    cout << "\n=== UNMATCHED PASSENGERS ===" << endl;
    for (const auto& p : pManager.getPassengers()) {
        bool isMatched = false;
        for (const auto& r : matchedRoutes) {
            if (r.getPassenger()->getId() == p->getId()) {
                isMatched = true;
                break;
            }
        }
        if (!isMatched) cout << p->getDeets() << endl;
    }
}
