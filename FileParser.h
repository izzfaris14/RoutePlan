#pragma once
#include<string>
#include<ctime>

class FileParser {
public:
	vector<Passenger> loadPass(string fileName);
	vector<Shuttle> loadShuttles(string fileName);
};