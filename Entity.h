#pragma once

#include <string>
#include<ctime>

using namespace std;

class Entity {
	string id;
	string dest;
	time_t time;

public:
	Entity(string id, string dest, time_t time);
	virtual ~Entity() = default;

	virtual void displayInfo() const;
	string getId() const;
	string getDest() const;
	time_t getTime() const;
};
