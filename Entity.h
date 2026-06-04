#pragma once

#include <string>
#include<ctime>

using namespace std;

class Entity {
	string id;
	string dest;
	string timeStr;

public:
	Entity(string id, string dest, string timeStr);
	virtual ~Entity() = default;

	virtual void displayInfo() const;
	string getId() const;
	string getDest() const;
	string getTimeStr() const;
};
