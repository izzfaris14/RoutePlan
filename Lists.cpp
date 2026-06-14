
#include<iostream>
#include "ShuttleList.h"
#include "PassList.h"
#include <fstream>
#include <sstream>

using namespace std;

ShuttleList::ShuttleList(vector<Shuttle> loadedData) {
	shuttleDB = loadedData;
}

Shuttle ShuttleList::getShuttle(int index) const {
	return shuttleDB[index]; 
}