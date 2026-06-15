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
      
            if (p->getDest() == s->getDest()) {
          
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
    for (const auto& route : matchedRoutes) {
        outFile << route.checkDest() << ", " << route.checkTime() << endl;
    }
    outFile.close();
    cout << "Matched routes written to file: " << fileName << endl;
}