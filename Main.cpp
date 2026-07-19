#include "SchedRepo.h"
#include "SchedGenerator.h"
#include "UIControl.h"
#include "FileParser.h"
#include <iostream>

using namespace std;

int main() {
	SchedRepo repo;
	SchedGenerator generator;
	FileParser parser;
	UIControl* ui UIControl::getInstance();

	cout << "system initializing\n";

	parser.loadShuttles("shuttles.txt", repo);
	parser.loadPassengers("passenger.txt", repo);

	generator.generateMatches(repo);

	ui->displayMatches(repo);

	return 0;
}